#include "print.h"
#include "sbi.h"

void puts(char *s) {
	int i=0;
	for(i=0;s[i];i++)
    		sbi_ecall(0x1,0x0,s[i],0,0,0,0,0);
	return;
}

void puti(int x) {
	int a=x,i,res=1;
	while(a/=10){
		res=res*10;
	}
	a=x;
	while(res){
		sbi_ecall(0x1,0x0,a/res+'0',0,0,0,0,0);
		a=a%res;
		res=res/10;
	}
	return;
}
