#include <stdio.h>
#include "reg.h"
#include "flow.h"
extern unsigned char vmcode[1024];
char flags[7] = {0};
void interpret_cmp(unsigned char arg1, unsigned char arg2){
    char reg1 = define_register(arg1);
    char reg2 = define_register(arg2);
    int reg1_value = (int)describe_register(arg1);
    int reg2_value = (int)describe_register(arg2);
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    CMP    |   %c   |   %c   | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, reg1, reg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    registers.f = 0;
    printf("Compare %c %c\n", describe_register(arg1), describe_register(arg2));
    if ( reg1_value < reg2_value ){ printf("%c < %c \n", reg1, reg2); registers.f |= 2;}
    if ( reg1_value > reg2_value ){ printf("%c > %c \n", reg1, reg2); registers.f |= 16;}
    if ( reg1_value == reg2_value ){ printf("%c = %c \n", reg1, reg2); registers.f |= 4;}
    if ( reg1_value != reg2_value ){ printf("%c != %c \n", reg1, reg2); registers.f |= 8;}
    if ( !reg1_value && !reg2_value ){ printf("!%c && !%c \n", reg1, reg2); registers.f |= 1;}
}


void describe_flags(unsigned char a1){    
int v2 = 0;
  if ( (a1 & 2) != 0 )
    flags[v2++] = 'L';
  if ( (a1 & 8) != 0 )
    flags[v2++] = 'G';
  if ( (a1 & 4) != 0 )
    flags[v2++] = 'E';
  if ( (a1 & 1) != 0 )
    flags[v2++] = 'N';
  if ( (a1 & 0x10) != 0 )
    flags[v2++] = 'Z';
  if ( !a1 )
    flags[v2++] = '*';
  flags[v2] = 0;
  
}



int interpret_jmp(unsigned char flag, unsigned char reg){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    JMP    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
           registers.i, flag, reg,
           registers.a, registers.b, registers.c, registers.d,
           registers.s, registers.i, registers.f);
    describe_flags(flag);
    printf("[j] JMP %s %c\n", flags , define_register(reg));
    if ( flag && (flag & registers.f) == 0 )
        return puts("[*] ... NOT TAKEN");
    puts("[*] ... TAKEN\n");
    printf("[*] Jumping to %d\n", (int)describe_register(reg));
    registers.i = describe_register(reg);
    return 0;
}

