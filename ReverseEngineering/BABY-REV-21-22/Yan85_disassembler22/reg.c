#include "reg.h"
#include <stdio.h>



struct reg registers = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};
extern unsigned char REGISTERS[];

// 0 - REG_A
// 1 - REG_B
// 2 - REG_C
// 3 - REG_D
// 4 - REG_S
// 5 - REG_I
// 6 - REG_F

int set_register(unsigned char reg, unsigned char value){ // sets the value of the register
    if ((reg & REGISTERS[0]) != 0)
        registers.a = value;
    if ((reg & REGISTERS[1]) != 0)
        registers.b = value;
    if ((reg & REGISTERS[2]) != 0)
        registers.c = value;
    if ((reg & REGISTERS[3]) != 0)  
        registers.d = value;
    if ((reg & REGISTERS[4]) != 0)
        registers.s = value;
    if ((reg & REGISTERS[5]) != 0)
        registers.i = value;
    if ((reg & REGISTERS[6]) != 0)
        registers.f = value;
    return 0;
}

unsigned char describe_register(unsigned char reg){ //returns the value inside the register
    if ((reg & REGISTERS[0]) != 0)
        return registers.a;
    if ((reg & REGISTERS[1]) != 0)
        return registers.b;
    if ((reg & REGISTERS[2]) != 0)
        return registers.c;
    if ((reg & REGISTERS[3]) != 0)
        return registers.d;
    if ((reg & REGISTERS[4]) != 0)
        return registers.s;
    if ((reg & REGISTERS[5]) != 0)
        return registers.i;
    if ((reg & REGISTERS[6]) != 0)
        return registers.f;    
    return '?';
}

unsigned char define_register(unsigned char reg){ //returns the name of the register depending on the argument
    if((reg & REGISTERS[0]) != 0)
        return 'a';
    if((reg & REGISTERS[1]) != 0)
        return 'b';
    if((reg & REGISTERS[2]) != 0)
        return 'c';
    if((reg & REGISTERS[3]) != 0)  
        return 'd';
    if((reg & REGISTERS[4]) != 0)  
        return 's';
    if((reg & REGISTERS[5]) != 0)
        return 'i';
    if((reg & REGISTERS[6]) != 0)
        return 'f';
    return '?';
}


int interpret_imm(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    IMM    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, arg1, arg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    return set_register(arg1, arg2);
}
