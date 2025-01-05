#include "reg.h"
#include <stdio.h>

#define REG_A 0x40
#define REG_B 0x1
#define REG_C 0x10
#define REG_D 0x2
#define REG_S 0x4
#define REG_I 0x8
#define REG_F 0x20

struct reg registers = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};


int set_register(unsigned char reg, unsigned char value){ // sets the value of the register
    switch (reg)
    {
    case REG_S:
        registers.s = value;
        break;
    case REG_C:
        registers.c = value;
        break;
    case REG_I:
        registers.i = value;
        printf("Jump to %d %#hhx \n", (int)value, value);
        break;
    case REG_D:
        registers.d = value;
        break;
    case REG_F:
        registers.f = value;
        break;
    case REG_B:        
        registers.b = value;
        break;
    case REG_A:
        registers.a = value;
        break;
    default:
        return -1;
    }
    return 0;
}

unsigned char describe_register(unsigned char reg){ //returns the value inside the register
    switch (reg)
    {
    case REG_S:
        return registers.s;
        break;
    case REG_C:
        return registers.c;
        break;
    case REG_I:
        return registers.i;
        break;
    case REG_D:
        return registers.d;
        break;
    case REG_F:
        return registers.f;
        break;
    case REG_B:
        return registers.b;
        break;
    case REG_A:
        return registers.a;
        break;
    default:
        return '?';
    }
}

unsigned char define_register(unsigned char reg){ //returns the name of the register depending on the argument
    
    switch (reg)
    {
    case REG_S:
        return 's';
        break;
    case REG_C:
        return 'c';
        break;
    case REG_I:
        return 'i';
        break;
    case REG_D:
        return 'd';
        break;
    case REG_F:
        return 'f';
        break;
    case REG_B:
        return 'b';
        break;
    case REG_A:
        return 'a';
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
