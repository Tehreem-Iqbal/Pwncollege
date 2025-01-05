## How did I get the flag...

#### Challenge statement:
Reverse engineer this custom emulator and architecture, and write your own custom shellcode to get the flag, with a twist. This is the final boss. Are you a true Yan-head?

##### Hmm.. What its all aabout? 

**Yan85 Architecture**
This custom emulator interprets the instruction given to it in its own way. Its has its own instruction set, operations, registers, flags and syscalls as well
After seeing the disassembly in ida. We will get to know the following information about yan85 architecture:
  - It has total of 7 registers named a, b, c, d, s, i, f. a,b,c and d being general register. i being the instruction pointer, s is stack pointer and f for jump manipulation
  - Total of 8 operations IMM, STK, STM, LDM, ADD, CMP, JMP, SYSCALL
  - 6 system calls: open, read_memory, read_code, write, sleep, exit
  - Some reserved space in data section for emulator's code, memory section / stack
  - EACH INSTRUCTION IS 3 BYTES ie; operation:arg1:arg2 (order may change depending on the binary) 
    
Lets have an example instruction to see how this emulator work: 804001
  - Now, lets suppose the order of instruction is arg1:arg2:operation
  - This means, operation = 01, arg1 = 80, arg2 = 40
  - The emulator will first determine which operation it is by comparing the opcode 
    Note:  Each operation have a value in base 2 from 1 to 128, Same is the case with registers and system calls
  - Suppose the operation 01 is for IMM. It will then interpret arg1 as register, and determine which register it is. and arg2 as a value to place in the register.
 
So, this challenge expects user input in the form of yancode by determining the value of each register, operation and syscall. And then it will execute that user given instructions.
But the twist in this challenge is, it randomizes the values of operations, registers and system calls depending on the flag(the flag that we are actually looking for). Lets have a look at randomization process:
  - Set seed value based on the flag "pwn.college{sdjijd}"
```
unsigned __int64 flag_seed()
{
  unsigned int seed; 
  unsigned int i; 
  int fd; 
  _QWORD buf[17]; 
  unsigned __int64 v5;

  v5 = __readfsqword(0x28u);
  memset(buf, 0, 128);
  fd = open("/flag", 0);
  if ( fd < 0 )
    __assert_fail("fd >= 0", "/challenge/babyrev-level-22-0.c", 0x20u, "flag_seed");
  if ( read(fd, buf, 0x80uLL) <= 0 )
    __assert_fail("read(fd, flag, 128) > 0", "/challenge/babyrev-level-22-0.c", 0x21u, "flag_seed");
  seed = 0;
  for ( i = 0; i <= 0x1F; ++i )
    seed ^= *((_DWORD *)buf + (int)i);
  srand(seed);
  memset(buf, 0, 0x80uLL);
  return __readfsqword(0x28u) ^ v5;
}
```
  - Generating random values and do shuffling:
  ```
  __int64 rerandomize()
{
  __int64 result; // rax

  shuffle_values();
  SPEC_REG_A = VALUES;
  SPEC_REG_B = byte_6011;
  SPEC_REG_C = byte_6012;
  SPEC_REG_D = byte_6013;
  SPEC_REG_S = byte_6014;
  SPEC_REG_I = byte_6015;
  SPEC_REG_F = byte_6016;
  shuffle_values();
  INST_IMM = VALUES;
  INST_STK = byte_6011;
  INST_ADD = byte_6012;
  INST_STM = byte_6013;
  INST_LDM = byte_6014;
  INST_JMP = byte_6015;
  INST_CMP = byte_6016;
  INST_SYS = byte_6017;
  shuffle_values();
  SYS_OPEN = VALUES;
  SYS_READ_MEMORY = byte_6011;
  SYS_READ_CODE = byte_6012;
  SYS_WRITE = byte_6013;
  SYS_SLEEP = byte_6014;
  SYS_EXIT = byte_6015;
  shuffle_values();
  FLAG_L = byte_6011;
  FLAG_G = byte_6012;
  FLAG_E = byte_6013;
  FLAG_N = byte_6014;
  result = (unsigned __int8)byte_6015;
  FLAG_Z = byte_6015;
  return result;
}
  ```
Shuffling:
```
void shuffle_values()
{
  for ( i = 0; i <= 65534; ++i )
  {
    v3 = rand() % 8;
    v0 = rand();
    v1 = VALUES[v3];
    VALUES[v3] = VALUES[v0 % 8];
    VALUES[v0 % 8] = v1;
  }
}
```

22.0 was pretty simple to solve
So, I ran the challenge for differnt inputs and observed the trace outputs and guessed all the values.
How did i check the instructions :
``` echo -e  '\x40\x02\x40' | ./babyrev-level-22-0 ```


![Screenshot from 2025-01-05 21-45-48](https://github.com/user-attachments/assets/7bce2022-76f2-4b52-a2d2-424d66bd2ebc)
So, this output means 40 is a syscall opcode, 02 is open syscall and 40 is register d. So in this ways, i figured out all the opcode values. 
