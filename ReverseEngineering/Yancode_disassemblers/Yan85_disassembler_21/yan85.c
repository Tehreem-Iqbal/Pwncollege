#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>  
#include "reg.h"
#include "stack.h"
#include "flow.h"
#include "mem.h"
// 01 stm 02 cmp 04: imm 08 stk 10 ldm 20 add 40 sys 80 jmp
// 02 c 04 b 08 f 10 s 20 i 40 d 80 a
// 0x02,0x20,0x00,
// arg2, arg1, operation
unsigned char vmcode[1024] = {
      //write "flag" string to registers
                    0x2f,0x80,0x04,
                    0x66,0x04,0x04,
                    0x6C,0x02,0x04,
                    0x61,0x40,0x04,
                    0x67,0x08,0x04,
                                //push registers to stack
                    0x80,0x00,0x08,
                    0x04,0x00,0x08,
                    0x02,0x00,0x08,
                    0x40,0x00,0x08,
                    0x08,0x00,0x08,
                                // set a, b, c and syscall open
                    0x01,0x80,0x04,
                    0x00,0x04,0x04,
                    0x00,0x02,0x04,
                    0x40,0x20,0x40,
                                // set a =d, b , c and syscall read_mem
                    0x00,0x80,0x04,
                    0x40,0x80,0x20, 
                    0x66,0x08,0x04,
                    0xff,0x02,0x04,
                    0x40,0x40,0x40,
                                // set a, b, c and syscall write_mem
                    0x01,0x80,0x04,
                    0x40,0x40,0x40,
                                
                                };

int interpret_add(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    ADD    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
        registers.i, arg1, arg2,
        registers.a, registers.b, registers.c, registers.d,
        registers.s, registers.i, registers.f);
    //printf("[s] ADD %c %c\n", define_register(arg1), define_register(arg2));
    int sum = (int)describe_register(arg1) + (int)describe_register(arg2);
    set_register(arg1, sum);
}

enum arch_syscall{
    SYSCALL_OPEN = 0x20,
    SYSCALL_WRITE_MEM = 0x8,
    SYSCALL_READ_MEM = 0x4,
    SYSCALL_READ_CODE = 0x10,
    SYSCALL_SLEEP = 0x1,
    SYSCALL_EXIT = 0x02
};

int interpret_sys(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    SYS    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
           registers.i, arg1, arg2,
           registers.a, registers.b, registers.c, registers.d,
           registers.s, registers.i, registers.f);
    int ret;
    switch (arg1)
    {
    case SYSCALL_WRITE_MEM:
        printf("[*] b: %d , %d\n", (int)registers.b,(int)registers.b+768);
        printf("[*] write(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[(int)registers.b+768], registers.c);
        ret = write(registers.a, &vmcode[(int)registers.b + 768], registers.c);
        printf("%s\n",&vmcode[registers.b] );
        break;
    case SYSCALL_OPEN:
        printf("[*] open(%p ,%#hhx, %#hhx)\n",  &vmcode[registers.a],registers.b ,registers.c);
        ret = open(&vmcode[registers.a + 768], (int)registers.b,  (int)registers.c);
        if (ret == -1) {
        printf("Error opening file: %s\n", strerror(errno));
        }
        write(1,&vmcode[registers.a + 768], 10 );
        printf("\n");
        break;
    case SYSCALL_READ_CODE:
        printf("[*] read_code(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[registers.b * 3] , registers.c);
        ret = read(registers.a, &vmcode[registers.b * 3] , registers.c ); // read_code
        printf("%s\n",&vmcode[registers.b * 3] );
        break;
    case SYSCALL_SLEEP:
        printf("[*] sleep(%#hhx)\n", registers.a);
        ret = sleep(registers.a);
        break;
    case SYSCALL_READ_MEM:
        printf("[*] read_memory(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[registers.b+768] , registers.c);
        ret = read(registers.a, &vmcode[registers.b+768] , registers.c ); //read_memory
        printf("%s\n",&vmcode[registers.b] );
        break;
    case SYSCALL_EXIT:
        printf("[*] exit(%#hhx)\n", registers.a);
        //exit(registers.a);
        break;
    default:
        return -1;
    }
    set_register(arg2, ret);
    return 0;
}

enum arch_inst {
    INST_LDM = 0x40,
    INST_STM = 0x20,
    INST_ADD = 0x10,
    INST_STK = 0x2,
    INST_JMP = 0x80,
    INST_CMP = 0x1,
    INST_IMM = 0x4,
    INST_SYS = 0x8
};

int interpret_instruction(unsigned  char operation, unsigned  char arg1, unsigned  char arg2){

    switch (operation)
    {
    case INST_SYS:
        interpret_sys(arg1, arg2);
        break;
    case INST_STM:
        interpret_stm(arg1, arg2);
        break;
    case INST_IMM:
        interpret_imm(arg1, arg2);
        break;
    case INST_JMP:
        interpret_jmp(arg1, arg2);
        break;
    case INST_CMP:
        interpret_cmp(arg1, arg2);
        break;
    case INST_STK:
        interpret_stk(arg1, arg2);
        break;
    case INST_LDM:
        interpret_ldm(arg1, arg2);
        break;
    case INST_ADD:
        interpret_add(arg1, arg2);
        break;
    default:
        return -1;
    }
    return 0;
}

int main()
{   

    unsigned char operation, arg1, arg2;
  
    while(registers.i < 228){
        arg2 = vmcode[3*registers.i];
        arg1 = vmcode[3*registers.i + 1];
        operation = vmcode[3*registers.i + 2];
        registers.i =  registers.i + 1;
        interpret_instruction(operation, arg1, arg2);    
    }

    return 0;
}


//0x20, 0xb9, 0x20, 0x4, 0x20, 0x8, 0x4, 0x10, 0x0, 0x4, 0x40, 0x0, 0x4, 0x20, 0x0, 0x4, 0x0, 0x20, 0x4, 0x0, 0x40, 0x4, 0x0, 0x10, 0x20, 0x96, 0x8, 0x20, 0x1, 0x40, 0x2, 0x4, 0x40, 0x20, 0x43, 0x1, 0x4, 0x1, 0x0, 0x20, 0x4f, 0x1, 0x4, 0x1, 0x0, 0x20, 0x52, 0x1, 0x4, 0x1, 0x0, 0x20, 0x52, 0x1, 0x4, 0x1, 0x0, 0x20, 0x45, 0x1, 0x4, 0x1, 0x0, 0x20, 0x43, 0x1, 0x4, 0x1, 0x0, 0x20, 0x54, 0x1, 0x4, 0x1, 0x0, 0x20, 0x21, 0x1, 0x4, 0x1, 0x0, 0x20, 0x20, 0x1, 0x4, 0x1, 0x0, 0x20, 0x59, 0x1, 0x4, 0x1, 0x0, 0x20, 0x6f, 0x1, 0x4, 0x1, 0x0, 0x20, 0x75, 0x1, 0x4, 0x1, 0x0, 0x20, 0x72, 0x1, 0x4, 0x1, 0x0, 0x20, 0x20, 0x1, 0x4, 0x1, 0x0, 0x20, 0x66, 0x1, 0x4, 0x1, 0x0, 0x20, 0x6c, 0x1, 0x4, 0x1, 0x0, 0x20, 0x61, 0x1, 0x4, 0x1, 0x0, 0x20, 0x67, 0x1, 0x4, 0x1, 0x0, 0x20, 0x3a, 0x1, 0x4, 0x1, 0x0, 0x20, 0xa, 0x1, 0x4, 0x1, 0x0, 0x20, 0x14, 0x20, 0x20, 0x1, 0x10, 0x8, 0x1, 0x1, 0x20, 0x2f, 0x1, 0x20, 0x80, 0x20, 0x1, 0x1, 0x20, 0x20, 0x66, 0x1, 0x20, 0x81, 0x20, 0x1, 0x1, 0x20, 0x20, 0x6c, 0x1, 0x20, 0x82, 0x20, 0x1, 0x1, 0x20, 0x20, 0x61, 0x1, 0x20, 0x83, 0x20, 0x1, 0x1, 0x20, 0x20, 0x67, 0x1, 0x20, 0x84, 0x20, 0x1, 0x1, 0x20, 0x20, 0x0, 0x1, 0x20, 0x85, 0x20, 0x1, 0x1, 0x20, 0x20, 0x80, 0x10, 0x20, 0x0, 0x40, 0x8, 0x1, 0x2, 0x20, 0x0, 0x40, 0x2, 0x4, 0x40, 0x20, 0xff, 0x20, 0x20, 0x0, 0x10, 0x2, 0x1, 0x10, 0x8, 0x1, 0x10, 0x20, 0x0, 0x40, 0x2, 0x4, 0x40, 0x20, 0x0, 0x20, 0x2, 0x1, 0x20, 0x20, 0x1, 0x10, 0x8, 0x1, 0x1, 0x20, 0x0, 0x10, 0x8, 0x0, 0x20, 0x4, 0x10, 0x0, 0x4, 0x40, 0x0, 0x4, 0x20, 0x0, 0x20, 0x1, 0x40, 0x2, 0x4, 0x40, 0x20, 0x4b, 0x1, 0x4, 0x1, 0x0, 0x20, 0x45, 0x1, 0x4, 0x1, 0x0, 0x20, 0x59, 0x1, 0x4, 0x1, 0x0, 0x20, 0x3a, 0x1, 0x4, 0x1, 0x0, 0x20, 0x20, 0x1, 0x4, 0x1, 0x0, 0x20, 0x5, 0x20, 0x20, 0x1, 0x10, 0x8, 0x1, 0x1, 0x4, 0x0, 0x20, 0x4, 0x0, 0x40, 0x4, 0x0, 0x10, 0x4, 0x10, 0x0, 0x4, 0x40, 0x0, 0x4, 0x20, 0x0, 0x20, 0x30, 0x40, 0x20, 0xb, 0x20, 0x20, 0x0, 0x10, 0x8, 0x1, 0x10, 0x4, 0x0, 0x20, 0x4, 0x0, 0x40, 0x4, 0x0, 0x10, 0x20, 0x2, 0x8, 0x20, 0x1, 0x40, 0x2, 0x4, 0x40, 0x20, 0x49, 0x1, 0x4, 0x1, 0x0, 0x20, 0x4e, 0x1, 0x4, 0x1, 0x0, 0x20, 0x43, 0x1, 0x4, 0x1, 0x0, 0x20, 0x4f, 0x1, 0x4, 0x1, 0x0, 0x20, 0x52, 0x1, 0x4, 0x1, 0x0, 0x20, 0x52, 0x1, 0x4, 0x1, 0x0, 0x20, 0x45, 0x1, 0x4, 0x1, 0x0, 0x20, 0x43, 0x1, 0x4, 0x1, 0x0, 0x20, 0x54, 0x1, 0x4, 0x1, 0x0, 0x20, 0x21, 0x1, 0x4, 0x1, 0x0, 0x20, 0xa, 0x1, 0x4, 0x1, 0x0, 0x20, 0xb, 0x20, 0x20, 0x1, 0x10, 0x8, 0x1, 0x1, 0x20, 0x1, 0x10, 0x8, 0x0, 0x20, 0x20, 0x30, 0x10, 0x20, 0x75, 0x40, 0x20, 0x9, 0x20, 0x20, 0x2, 0x1, 0x2, 0x8, 0x1, 0x4, 0x1, 0x0, 0x20, 0xa3, 0x8, 0x20, 0x0, 0x20, 0x10, 0x20, 0x1, 0x20, 0x9, 0x1, 0x80, 0x1, 0x4, 0x20, 0x79, 0x1, 0x80, 0x1, 0x3, 0x2, 0x20, 0x10, 0x2, 0x20, 0x40, 0x20, 0xff, 0x1, 0x2, 0x1, 0x10, 0x2, 0x1, 0x40, 0x4, 0x10, 0x0, 0x4, 0x40, 0x0, 0x40, 0x10, 0x10, 0x40, 0x40, 0x40, 0x10, 0x40, 0x10, 0x4, 0x0, 0x40, 0x4, 0x0, 0x10, 0x20, 0xb7, 0x1, 0x80, 0x1, 0x8, 0x20, 0xff, 0x1, 0x2, 0x1, 0x20, 0x20, 0x0, 0x1, 0x10, 0x1, 0x20, 0x20, 0xa5, 0x1, 0x80, 0x1, 0x8, 0x4, 0x20, 0x1, 0x4, 0x0, 0x8, 0x20, 0x8d, 0x1, 0x20, 0x73, 0x20, 0x1, 0x1, 0x20, 0x20, 0x23, 0x1, 0x20, 0x74, 0x20, 0x1, 0x1, 0x20, 0x20, 0x16, 0x1, 0x20, 0x75, 0x20, 0x1, 0x1, 0x20, 0x20, 0xd2, 0x1, 0x20, 0x76, 0x20, 0x1, 0x1, 0x20, 0x20, 0x77, 0x1, 0x20, 0x77, 0x20, 0x1, 0x1, 0x20, 0x20, 0x4f, 0x1, 0x20, 0x78, 0x20, 0x1, 0x1, 0x20, 0x20, 0x6a, 0x1, 0x20, 0x79, 0x20, 0x1, 0x1, 0x20, 0x20, 0x73, 0x1, 0x20, 0x7a, 0x20, 0x1, 0x1, 0x20, 0x20, 0x93, 0x1, 0x20, 0x7b, 0x20, 0x1, 0x1, 0x20, 0x20, 0x7f, 0x1, 0x20, 0x7c, 0x20, 0x1, 0x1, 0x20, 0x20, 0x79, 0x1, 0x20, 0x7d, 0x20, 0x1, 0x1, 0x20, 0x20, 0x59, 0x8, 0x0, 0x0, 0x0