#include <stdio.h>
#include "reg.h"
#include "stack.h"

extern unsigned char vmcode[1024];
int push(unsigned char reg){ // push reg values to the stack
    //printf("[*] Pushing %c\n", define_register(reg));
    switch (reg)
    {
    case 0x1:
        vmcode[registers.s + 768] = registers.d;
        break;
    case 0x2:
        vmcode[registers.s + 768] = registers.f;
        break;
    case 0x4:
        vmcode[registers.s + 768] = registers.s;
        break;
    case 0x8:
        vmcode[registers.s + 768] = registers.i;
        break;
    case 0x10:
        vmcode[registers.s + 768] = registers.a;
        break;
    case 0x20:
        vmcode[registers.s + 768] =  registers.c;
        break;
    case 0x40:
        vmcode[registers.s + 768] = registers.b;
        break;
    default:
        return -1;
    }
    //printf("vmcode[%d] = %c\n", registers.s + 768, vmcode[registers.s + 768]);
    return 0;
    
}

int pop(unsigned char reg){ // pop register value into the stack 
    //printf("[*] Popping %c\n", define_register(reg));
    switch (reg)
    {
    case 0x1:
        registers.d = vmcode[registers.s + 768];
        break;
    case 0x2:
        registers.f = vmcode[registers.s + 768];
        break;
    case 0x4:
        registers.s = vmcode[registers.s + 768];
        break;
    case 0x8:
        registers.i = vmcode[registers.s + 768];
        //printf("Jump to %d\n", (int)vmcode[registers.s + 768]);
        break;
    case 0x10:
        registers.a = vmcode[registers.s + 768];
        break;
    case 0x20:
        registers.c = vmcode[registers.s + 768];
        break;
    case 0x40:
        registers.b = vmcode[registers.s + 768];
        break;
    default:
        return -1;
    }
    return 0;
    
}

int interpret_stk(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    STK    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
           registers.i, arg1, arg2,
           registers.a, registers.b, registers.c, registers.d,
           registers.s, registers.i, registers.f);
    if(arg2 != 0x0) { registers.s= (int)registers.s+1; push(arg2); }
    if(arg1 != 0x0) {  pop(arg1); registers.s = (int)registers.s - 1 ;  }
}