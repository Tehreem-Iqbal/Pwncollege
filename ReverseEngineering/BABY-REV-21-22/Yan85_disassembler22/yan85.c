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



// operations, arg2, arg1
unsigned char vmcode[1024] = {
                    // set a, b, c
                    0x01,0x2f,0x01,
                    0x01,0x66,0x02,
                    0x01,0x6C,0x04,
                    0x01,0x61,0x08,
                    0x01,0x67,0x10,
                    //push registers to stack
                    //0x20,0x00,0x02,
                    0x02,0x10,0x00,
                    0x02,0x40,0x00,
                    0x02,0x04,0x00,
                    0x02,0x01,0x00,
                    // set a, b, c and syscall open
                    0x01,0x01,0x01,
                    0x01,0x00,0x02,
                    0x01,0x00,0x04,
                    0x80,0x08,0x01,
                    // set a =d, b , c and syscall read_mem
                    0x01,0x00,0x10,
                    0x04,0x08,0x01,
                    0x01,0x66,0x20,
                    0x01,0xff,0xc0,
                    0x80,0x08,0x02,
                    // set a, b, c and syscall write_mem
                    0x01,0x01,0x10,
                    0x80,0x08,0x08,
                    };



unsigned char VALUES[] = { 
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 
};

unsigned char REGISTERS[] = {0};
    // 0 - REG_A
    // 1 - REG_B
    // 2 - REG_C
    // 3 - REG_D
    // 4 - REG_S
    // 5 - REG_I
    // 6 - REG_F

unsigned char SYSCALLS[] = {0};
    // 0 - SYS_OPEN
    // 1 - SYS_READ_MEMORY
    // 2 - SYS_READ_CODE
    // 3 - SYS_WRITE
    // 4 - SYS_SLEEP
    // 5 - SYS_EXIT

unsigned char INSTRUCTIONS[] = {0};
    // 0 - INST_IMM 
    // 1 - INST_STK
    // 2 - INST_ADD
    // 3 - INST_STM
    // 4 - INST_LDM
    // 5 - INST_JMP
    // 6 - INST_CMP
    // 7 - INST_SYS

unsigned char FLAGS[5] = {0};
    // 0 - FLAG_L
    // 1 - FLAG_G
    // 2 - FLAG_E
    // 3 - FLAG_N
    // 4 - FLAG_Z
void shuffle_values(){
    int i;
    unsigned char temp = 0x0;
    for (i = 0; i < 65534; i++) {
        int v1 = rand() % 8;
        int v2 = rand() % 8;
        temp = VALUES[v1];
        VALUES[v1] = VALUES[v2];
        VALUES[v2] = temp;
    }
}
void rerandomize(){
    int i;
    shuffle_values();
    for (i = 0; i < 8; i++) {
    REGISTERS[i] = VALUES[i];
    }
    shuffle_values();
    for (i = 0; i < 8; i++) {
    INSTRUCTIONS[i] = VALUES[i];
    }
    shuffle_values();
    for (i = 0; i < 6; i++) {
        SYSCALLS[i] = VALUES[i];
    }
    shuffle_values();
    for (i = 0; i < 5; i++) {
        FLAGS[i] = VALUES[i];
    }
}

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

// 0 - SYS_OPEN
// 1 - SYS_READ_MEMORY
// 2 - SYS_READ_CODE
// 3 - SYS_WRITE
// 4 - SYS_SLEEP
// 5 - SYS_EXIT

int interpret_sys(unsigned char arg1, unsigned char arg2){
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" | %-3d |    SYS    | 0x%02hhX  |  0x%02hhX | a= 0x%02hhX | b= 0x%02hhX | c= 0x%02hhX | d= 0x%02hhX | s= 0x%02hhX | i= 0x%02hhX | f= 0x%02hhX |\n",
           registers.i, arg1, arg2,
           registers.a, registers.b, registers.c, registers.d,
           registers.s, registers.i, registers.f);
    int ret;
    if ((arg1 &  SYSCALLS[0]) !=0){
        printf("[*] open(%p ,%#hhx, %#hhx)\n",  &vmcode[registers.a],registers.b ,registers.c);
        ret = open(&vmcode[registers.a + 768], (int)registers.b,  (int)registers.c);
        if (ret == -1) {
        printf("Error opening file: %s\n", strerror(errno));
        }
        write(1,&vmcode[registers.a + 768], 10 );
        printf("\n");
    }
    else if ((arg1 &  SYSCALLS[1]) !=0){
        printf("[*] read_memory(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[registers.b+768] , registers.c);
        ret = read(registers.a, &vmcode[registers.b+768] , registers.c ); //read_memory
        printf("%s\n",&vmcode[registers.b] );
    }
    else if ((arg1 &  SYSCALLS[2]) !=0){
        printf("[*] read_code(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[registers.b * 3] , registers.c);
        ret = read(registers.a, &vmcode[registers.b * 3] , registers.c ); // read_code
        printf("%s\n",&vmcode[registers.b * 3] );
    }
    else if ((arg1 &  SYSCALLS[3]) !=0){
        printf("[*] write(%#hhx ,%p, %#hhx)\n", registers.a, &vmcode[(int)registers.b+768], registers.c);
        ret = write(registers.a, &vmcode[(int)registers.b + 768], registers.c);
        printf("%s\n",&vmcode[registers.b] );
    }
    else if ((arg1 &  SYSCALLS[4]) !=0){
        printf("[*] sleep(%#hhx)\n", registers.a);
        ret = sleep(registers.a);
    }
    else if ((arg1 &  SYSCALLS[5]) !=0){
        printf("[*] exit(%#hhx)\n", registers.a);
        //exit(registers.a);
    }
    else 
        printf("Unknown syscall\n");
    set_register(arg2, ret);
    return 0;
}

    // 0 - INST_IMM 
    // 1 - INST_STK
    // 2 - INST_ADD
    // 3 - INST_STM
    // 4 - INST_LDM
    // 5 - INST_JMP
    // 6 - INST_CMP
    // 7 - INST_SYS

int interpret_instruction(unsigned  char operation, unsigned  char arg1, unsigned  char arg2){
    if ((operation & INSTRUCTIONS[0]) !=0)
        interpret_imm(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[1]) !=0)
        interpret_stk(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[2]) !=0)
        interpret_add(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[3]) !=0)
        interpret_stm(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[4]) !=0)
        interpret_ldm(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[5]) !=0)
        interpret_jmp(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[6]) !=0)
        interpret_cmp(arg1, arg2);
    
    else if ((operation & INSTRUCTIONS[7]) !=0)
        interpret_sys(arg1, arg2);
    else 
        printf("Unknown operation\n");
    return 0;
}

int main()
{   
    unsigned int seed;
    unsigned char operation, arg1, arg2;

    for (seed = 0xffffff; seed <= 0xFFFFFFFF; ++seed) {
        registers.i = 0;
        srand(seed);
        rerandomize();
        printf("Seed: 0x%x (%u)\n", seed, seed);
        if (INSTRUCTIONS[7] == 0x40 && SYSCALLS[1] == 0X40 && REGISTERS[3] == 0x40 &&
            INSTRUCTIONS[2] == 0x20 && SYSCALLS[4] == 0x20 && REGISTERS[5] == 0x20 )
        {
            
            printf("%#hhx %#hhx %#hhx\n", INSTRUCTIONS[7], SYSCALLS[1], REGISTERS[3]);
            printf("%#hhx %#hhx %#hhx\n", INSTRUCTIONS[2], SYSCALLS[4], REGISTERS[3]);
            break;
        }
        // while(registers.i < 228){
        //     operation = vmcode[3*registers.i];
        //     arg2 = vmcode[3*registers.i + 1];
        //     arg1 = vmcode[3*registers.i + 2];
        //     registers.i =  registers.i + 1;
        //     interpret_instruction(operation, arg1, arg2);    
        // }
    }
    
    
    
    

    return 0;
}