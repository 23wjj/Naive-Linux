#include "syscall.h"
#include "proc.h"
#include "printk.h"
extern struct task_struct* current;
int sys_getpid(){
    return current->pid;
}
unsigned int sys_write(unsigned int fd, const char* buf, unsigned int count){
    if(fd==1){
        printk("%s",buf);
    	return count;
    }
}
