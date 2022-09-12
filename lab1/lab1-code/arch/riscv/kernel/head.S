.extern start_kernel

    .section .text.entry
    .globl _start
_start:
    # ------------------
    # - your code here -
    # ------------------
    #auipc sp,%hi(boot_stack_top)
    #addi sp,sp,%lo(boot_stack_top)
    #addi sp,sp,0x4
    
    la sp,boot_stack_top
    
    #auipc t0,%hi(start_kernel)
    #jalr ra,t0,%lo(start_kernel)
    
    call start_kernel

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 0x1000 # <-- change to your stack size

    .globl boot_stack_top
boot_stack_top:
