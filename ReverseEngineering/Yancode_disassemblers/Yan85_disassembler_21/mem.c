#include <stdio.h>
#include "reg.h"

#define REG_A 0x20
#define REG_B 0x10
#define REG_C 0x40
#define REG_D 0x4
#define REG_S 0x8
#define REG_I 0x2
#define REG_F 0x1

extern unsigned char vmcode[1024];

int interpret_ldm(unsigned char arg1, unsigned char arg2){ //load memory in register
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    LDM    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, arg1, arg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    //printf("[*] LDM %c = *%c\n", define_register(arg1), define_register(arg2));
    int mem = (int)describe_register(arg2);
    set_register(arg1, vmcode[mem + 768]);
}

int interpret_stm(unsigned char arg1, unsigned char arg2){ // store register in memory
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    STM    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, arg1, arg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    //printf("[*] STM *%c = %c\n", define_register(arg1), define_register(arg2));

    int mem = (int)describe_register(arg1);


    switch (arg2)
    {
    case REG_S:
        vmcode[mem + 768] = registers.s;
        break;
    case REG_C:
        vmcode[mem + 768] = registers.c;
        break;
    case REG_I:
        vmcode[mem + 768] = registers.i;
        break;
    case REG_D:
        vmcode[mem + 768] = registers.d;
        break;
    case REG_F:
        vmcode[mem + 768] = registers.f ;
        break;
    case REG_B:
        vmcode[mem + 768] = registers.b;
        break;
    case REG_A:
        vmcode[mem + 768] = registers.a;
        break;
    default:
        return -1;
    }

    //printf("vmcode[%d] = %#hhx\n", mem + 768, vmcode[mem + 768]);
    return 0;
    
}
