#include <stdio.h>
#include "reg.h"
extern unsigned char REGISTERS[];
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

    if ((arg2 & REGISTERS[0]) != 0)
        vmcode[mem + 768] = registers.a;
    if ((arg2 & REGISTERS[1]) != 0)
        vmcode[mem + 768] = registers.b;
    if ((arg2 & REGISTERS[2]) != 0)
        vmcode[mem + 768] = registers.c;
    if ((arg2 & REGISTERS[3]) != 0)
        vmcode[mem + 768] = registers.d;
    if ((arg2 & REGISTERS[4]) != 0)
        vmcode[mem + 768] = registers.s;
    if ((arg2 & REGISTERS[5]) != 0)
        vmcode[mem + 768] = registers.i;
    if ((arg2 & REGISTERS[6]) != 0)
        vmcode[mem + 768] = registers.f;

    //printf("vmcode[%d] = %#hhx\n", mem + 768, vmcode[mem + 768]);
    return 0;
    
}
