#include "types.h"
#define SYS_WRITE   64
#define SYS_GETPID  172

struct pt_regs{
    uint64 sepc;
    uint64 x31,x30,x29,x28,x27,x26,x25,x24,x23,x22,x21,x20,x19,x18,x17,x16,x15,x14,x13,x12,x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0; 
};

int sys_getpid();
unsigned int  sys_write(unsigned int fd, const char* buf, unsigned int count);
