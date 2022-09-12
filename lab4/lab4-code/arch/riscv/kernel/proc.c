//arch/riscv/kernel/proc.c

#include "defs.h"
#include "mm.h"
#include "proc.h"
#include "printk.h"
#include "rand.h"

extern unsigned long swapper_pg_dir[512];

extern void __dummy();
extern void __switch_to(struct task_struct* prev, struct task_struct* next);
extern char uapp_start[];
extern char uapp_end[];

struct task_struct* idle;           // idle process
struct task_struct* current;        //point to the current process
struct task_struct* task[NR_TASKS]; // store all processes

void task_init() {

    uint64 i;

    idle=(struct task_struct*)kalloc();
    idle->thread.sp=(uint64)idle+PGSIZE;
    idle->state=TASK_RUNNING;
    idle->counter=0;
    idle->priority=0;
    idle->pid=0;

    current=idle;
    task[0]=idle;
    for(i=1;i<NR_TASKS;i++){
         task[i]=(struct task_struct*)kalloc();
         task[i]->state=TASK_RUNNING;
         task[i]->counter=0;
         task[i]->pid=i;
         task[i]->priority=rand();
         task[i]->thread.ra=(uint64)__dummy;
         task[i]->thread.sp=(uint64)task[i]+PGSIZE;
         //allocate to store user_stack
         unsigned long * user_stack=kalloc();
         //allocate to store kernel page
         unsigned long * kernel_pg=kalloc();
         task[i]->pgd=(unsigned long)kernel_pg-PA2VA_OFFSET;
         for(int i=0;i<512;i++)
             kernel_pg[i]=swapper_pg_dir[i];
         create_mapping(kernel_pg,USER_END-PGSIZE,(unsigned long)user_stack-PA2VA_OFFSET,PGSIZE,0b10111);
         create_mapping(kernel_pg,USER_START,(unsigned long)uapp_start-PA2VA_OFFSET,(unsigned long)uapp_end-(unsigned long)uapp_start,0b11111);
         task[i]->thread.sstatus=csr_read(sstatus);
         task[i]->thread.sstatus|=0x00040020;
         //task[i]->thread.sstatus=(csr_read(sstatus))|0x00040020;
         csr_write(sstatus,task[i]->thread.sstatus);
         task[i]->thread.sepc=USER_START;
         task[i]->thread.sscratch=USER_END;
    }

    printk("...proc_init done!\n");

}
void dummy() {
    uint64 MOD = 1000000007;
    uint64 auto_inc_local_var = 0;
    int last_counter = -1;
    while(1) {
        if (last_counter == -1 || current->counter != last_counter) {
            last_counter = current->counter;
            auto_inc_local_var = (auto_inc_local_var + 1) % MOD;
            printk("[PID = %d] is running. auto_inc_local_var = %d thread space begin at %lx \n", current->pid, auto_inc_local_var,current);
        }
    }
}

void switch_to(struct task_struct* next) {
    struct task_struct *tmp=current;
    if(current==next);
    else{
        printk("switch to [PID = %d PRIORITY = %d COUNTER = %d]\n",next->pid,next->priority,next->counter);
        current=next;
        __switch_to(tmp,next);
    }
    return;
}

void do_timer(void) {
    if((current==idle)||(!(--current->counter)))
        schedule();
    return;
}
//shortest-job first
#ifdef SJF
int Findtask(void){
    uint64 i,index=-1;
    for(i=1;i<NR_TASKS;i++){
        if((task[i]->counter)&&(task[i]->state==TASK_RUNNING)){
            if((index==-1)||(task[i]->counter<task[index]->counter))
                index=i;
        }
    }
    return index;
}
#endif
//priority
#ifdef PRIORITY
int Findtask(void){
    uint64 i,index=-1;
    for(i=1;i<NR_TASKS;i++){
        if((task[i]->counter)&&(task[i]->state==TASK_RUNNING)){
            if((index==-1)||(task[i]->priority>task[index]->priority))
                index=i;
        }
    }
   return index;
}
#endif
void schedule(void){
    uint64 index,i;
    uint64 cnt=0;
    while((index=Findtask())==-1){
        for(i=1;i<NR_TASKS;i++){
            if(task[i]->state==TASK_RUNNING){
                task[i]->counter=(uint64)rand();
            }
       }
        cnt++;
    }
    if(cnt){
        for(i=1;i<NR_TASKS;i++){
            printk("SET [PID = %d PRIORITY = %d COUNTER = %d]\n",task[i]->pid,task[i]->priority,task[i]->counter);
        }
    }
    //printk("%x",(uint64)task[index]);
    //before=current;
    //current=task[index];
    switch_to(task[index]);
    return;
}

