// arch/riscv/include/proc.h

#include "types.h"

#define NR_TASKS  1+4

#define TASK_RUNNING    0 

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

typedef unsigned long* pagetable_t;

struct thread_info {
    uint64 kernel_sp;
    uint64 user_sp;
};

struct thread_struct {
    uint64 ra;
    uint64 sp;
    uint64 s[12];

    uint64 sepc,sstatus,sscratch;
};

struct task_struct {
    struct thread_info* thread_info;
    uint64 state;
    uint64 counter;
    uint64 priority;
    uint64 pid;      //thread ID

    struct thread_struct thread;
    
    pagetable_t pgd;
};

void task_init(); 

void do_timer();

void schedule();

void switch_to(struct task_struct* next);

void dummy();
