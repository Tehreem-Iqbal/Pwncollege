#include <stdio.h>
#include "reg.h"

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
    case 0x1:
        vmcode[mem + 768] = registers.d;
        break;
    case 0x2:
        vmcode[mem + 768] = registers.f;
        break;
    case 0x4:
        vmcode[mem + 768] = registers.s;
        break;
    case 0x8:
        vmcode[mem + 768] = registers.i;
        break;
    case 0x10:
        vmcode[mem + 768] = registers.a ;
        break;
    case 0x20:
        vmcode[mem + 768] = registers.c ;
        break;
    case 0x40:
        vmcode[mem + 768] = registers.b ;
        break;
    default:
        return -1;
    }

    //printf("vmcode[%d] = %#hhx\n", mem + 768, vmcode[mem + 768]);
    return 0;
    
}
