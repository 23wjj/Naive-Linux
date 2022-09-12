// trap.c

#include "printk.h"
#include "sbi.h"

extern void clock_set_next_event();

void trap_handler(unsigned long scause, unsigned long sepc) {
    unsigned long x=scause,y=sepc,xi,yi;
    xi=0x8000000000000000;
    if(x>=xi){
    	xi=0x8000000000000005;
	if(x==xi){
	    //a supervisor time interrupt
	    printk("kernel is running!\n");
	    printk("[S] Supervisor Mode Timer Interrupt\n");
	    clock_set_next_event();
	}
	else{
            //other interrupts
	    ;	
	}
    }
    else{
        ;//exception
    }
    return;
}
