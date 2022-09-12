# Naive-Linux ![Language](https://img.shields.io/badge/language-c-brightgreen)
A simple linux kernel, with function of thread scheduling, time interrupt, virtual address space, some system call and so on.

## Lab Instruction
* <https://zjusec.gitee.io/sys2lab-21fall/>
* <https://computer_architecture_cr_zju.gitee.io/sys3lab-2022-stu/>
## Tools
<a href="https://www.vim.org/" target="_blank"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/vim/vim-original.svg" alt="c" width="40" height="40"/> </a>
<a href="https://www.docker.com/" target="_blank"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/docker/docker-original-wordmark.svg" alt="docker" width="40" height="40"/> </a>
<a href="https://www.qemu.org" target="_blank"> <img src="https://www.vectorlogo.zone/logos/qemu/qemu-icon.svg" alt="QEMU" width="40" height="40"/> </a>
<a href="https://www.linux.org/" target="_blank"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" alt="linux" width="40" height="40"/> </a>

## File organization
|file|explanation|lab link|
|-|-|-|
|lab0/|RV64 内核引导(head.S & openSBI)|<https://zjusec.gitee.io/sys2lab-21fall/lab4/>|
|lab1/|RV64 时钟中断(entry.S(context switch) & trap handler & system call)|<https://zjusec.gitee.io/sys2lab-21fall/lab5/>|
|lab2/|RV64 内核线程调度(proc.c(schedule strategy with SJF & PRIORITY))|<https://zjusec.gitee.io/sys2lab-21fall/lab6/>|
|lab3/|RV64 虚拟内存管理(mm.c(create page table and fixed mapping))|<https://computer_architecture_cr_zju.gitee.io/sys3lab-2022-stu/lab3/>|
|lab4/|RV64用户模式|<https://computer_architecture_cr_zju.gitee.io/sys3lab-2022-stu/lab4/>|
|lab5/|RV64缺页异常以及fork机制(trap.c(handling page fault) & proc.c(create vma struct))|<https://computer_architecture_cr_zju.gitee.io/sys3lab-2022-stu/lab5/>|
