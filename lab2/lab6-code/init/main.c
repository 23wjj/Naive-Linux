#include "printk.h"
#include "sbi.h"
#include "proc.h"

extern void test();

int start_kernel() {

    printk(" Hello RISC-V\n");
    test(); // DO NOT DELETE !!!

	return 0;
}
