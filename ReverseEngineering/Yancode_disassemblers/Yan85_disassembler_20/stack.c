#include <stdio.h>
#include "reg.h"
#include "stack.h"
#define REG_A 0x40
#define REG_B 0x1
#define REG_C 0x10
#define REG_D 0x2
#define REG_S 0x4
#define REG_I 0x8
#define REG_F 0x20

extern unsigned char vmcode[1024];
int push(unsigned char reg){
    //printf("[*] Pushing %c\n", define_register(reg));
    switch (reg)
    {
    case REG_S:
        vmcode[registers.s + 768] = registers.s;
        break;
    case REG_C:
        vmcode[registers.s + 768] = registers.c;
        break;
    case REG_I:
        vmcode[registers.s + 768] = registers.i;
        break;
    case REG_D:
        vmcode[registers.s + 768] = registers.d;
        break;
    case REG_F:
        vmcode[registers.s + 768] = registers.f;
        break;
    case REG_B:
        vmcode[registers.s + 768] =  registers.b;
        break;
    case REG_A:
        vmcode[registers.s + 768] = registers.a;
        break;
    default:
        return -1;
    }
    //printf("vmcode[%d] = %c\n", registers.s + 768, vmcode[registers.s + 768]);
    return 0;
    
}

int pop(unsigned char reg){
    //printf("[*] Popping %c\n", define_register(reg));
    switch (reg)
    {
    case REG_S:
        registers.s = vmcode[registers.s + 768];
        break;
    case REG_C:
        registers.c = vmcode[registers.s + 768];
        break;
    case REG_I:
        registers.i = vmcode[registers.s + 768];
        printf("Jump to %d\n", (int)vmcode[registers.s + 768]);
        break;
    case REG_D:
        registers.d = vmcode[registers.s + 768];
        
        break;
    case REG_F:
        registers.f = vmcode[registers.s + 768];
        break;
    case REG_B:
        registers.b = vmcode[registers.s + 768];
        break;
    case REG_A:
        registers.a = vmcode[registers.s + 768];
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