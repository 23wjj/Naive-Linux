.extern start_kernel
.extern _traps
.extern mm_init
.extern task_init
.extern clock_set_next_event
    .section .text.init
    .globl _start
_start:
    la sp,boot_stack_top
    call mm_init
    call task_init
    
    #set stvec to _traps
    la t0,_traps
    #add t0,t0,t0
    #add t0,t0,t0
    csrw stvec,t0

    #set sie[STIE]=1
    csrr t1,sie
    addi t2,x0,32
    or t1,t1,t2
    csrw sie,t1
    
    #set first time interrupt
    
    #call clock_set_next_event
    rdtime t0
    li t1,10000000
    add a0,t1,t0
    add a1,x0,x0
    add a2,x0,x0
    add a3,x0,x0
    add a4,x0,x0
    add a5,x0,x0
    add a7,x0,x0
    add a6,x0,x0
    ecall
   
    #set sstatus[sie]=1
    csrr t1,sstatus
    addi t2,x0,2
    or t1,t1,t2
    csrw sstatus,t1
     
    #la sp,boot_stack_top
    #call mm_init
    #call task_init

    call start_kernel

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 4096 # <-- change to your stack size

    .globl boot_stack_top
boot_stack_top:
