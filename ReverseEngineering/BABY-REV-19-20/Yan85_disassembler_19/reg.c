#include "reg.h"
#include <stdio.h>


struct reg registers = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};

int set_register(unsigned char reg, unsigned char value){ // sets the value of the register
    switch (reg)
    {
    case 0x1:
        registers.d = value;
        break;
    case 0x2:
        registers.f = value;
        break;
    case 0x4:
        registers.s = value;
        break;
    case 0x8:
        registers.i = value;
        //printf("Jump to %d\n", (int)value);
        break;
    case 0x10:
        registers.a = value;
        break;
    case 0x20:
        registers.c = value;
        break;
    case 0x40:
        registers.b = value;
        break;
    default:
        return -1;
    }
    return 0;
}

unsigned char describe_register(unsigned char reg){ //returns the value inside the register
    switch (reg)
    {
    case 0x1:
        return registers.d;
        break;
    case 0x2:
        return registers.f;
        break;
    case 0x4:
        return registers.s;
        break;
    case 0x8:
        return registers.i;
        break;
    case 0x10:
        return registers.a;
        break;
    case 0x20:
        return registers.c;
        break;
    case 0x40:
        return registers.b;
        break;
    default:
        return '?';
    }
}

unsigned char define_register(unsigned char reg){ //returns the name of the register depending on the argument
    
    switch (reg)
    {
    case 0x1:
        return 'd';
        break;
    case 0x2:
        return 'f';
        break;
    case 0x4:
        return 's';
        break;
    case 0x8:
        return 'i';
        break;
    case 0x10:
        return 'a';
        break;
    case 0x20:
        return 'c';
        break;
    case 0x40:
        return 'b';
        break;
    default:
        return -1;
    }
}


int interpret_imm(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    IMM    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, arg1, arg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    return set_register(arg1, arg2);
}
