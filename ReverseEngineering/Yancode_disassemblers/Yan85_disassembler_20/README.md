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

**22.0 was pretty simple to solve**

So, I ran the challenge for differnt inputs and observed the trace outputs and guessed all the values.
How did i check the instructions :
``` echo -e  '\x40\x02\x40' | ./babyrev-level-22-0 ```


![Screenshot from 2025-01-05 21-45-48](https://github.com/user-attachments/assets/7bce2022-76f2-4b52-a2d2-424d66bd2ebc)

So, this output means 40 is a syscall opcode, 02 is open syscall and 40 is register d. So in this ways, i figured out all the opcode values. 
Corresponding to my flag, the opcode values were 
```
01 stm 02 cmp 04 imm 08 stk 10 ldm 20 add 40 sys 80 jmp
02 c 04 b 08 f 10 s 20 i 40 d 80 a
20 sleep 40 readmem
02 open 04 read_code
08 exit 01 write
```
My instruction set looked something like this
```
# set "/flag" string in a,b,c and d registers 
2f8004
660404
6C0204
614004
670804
# push a,b,c,d to stack
800008
040008
020008
400008
080008
# set a to 1( pointing to the stack), b and c to 0 for opening in readonly mode 
018004
000404
000204
400240 # open, return value (file descriptor) in register d
# set register a with value register d (fd), b (stack offset) , and c(no of bytes to read) and call read()
008004
408020
660804
ff0204
404040 # read at b offset in stack
# set a to 01 (standard output) and call write()
018004
400140
```
**Daaamn! 22.1 dont output any traceee....**
As usual, went to discord server... The only hint i got was, yoou need to guess the opcodes by observing the behavior of program. And look for exit codes. 
First of all, I checked for the instruction opcode pattern: arg1:arg2:operation. So, I started giving input and checking for the behavior and exit codes. If the exit code is 0, that means it did syscall exit
  
  - Tried for operation and arg1 combinations. For input: '\x10\x08\x80', exit code was 0. That means **80 is SYSCALL operation**. and **10 is the exit syscall**. For every other combination, the programm continued to run in a loop. Except for changing 04 as arg2. From this, i can guess that **04 is an unknown register**, I confirmed it by checking it for other combinations of arg1 and operation, it terminated at almost every other combination of input **BUT NOT ALL**.
  - When i tried 08 and 40 as syscalls opcodes (arg1) with 04 as register (arg2) the program continued to run. Why? Because when the arg1 doesnt match any of the syscall opcode, it continuos, whether its a valid register or not in arg2. So, we guessed that 08 and 04 are unknown syscalls.
  - Tried '\x04\x08\x80', turns out, the process is in sleep mode by checking ps -aux. Not sure that its sleep syscall because the process also showws S+ status if waiting for an input.
  - After searching for more help on discord. Got another hint: ONLY JUMP AND IMM operations that take a non register argument. This implies that if the program doesnt terminate on 04 (unknown register) as arg2, its IMM instruction. And if it does not crash on 04 on both as arg1 and arg2, it will be JMP (but we have no need to find the jmp instruction). Whooo , we found the **IMM opcode 08** :v:
  - Since, the exit status of exist syscall depend on register a, works as: ```exit(a)```, we can find the register a opcode. Setting an immidiate value in different register, and then do exit. If the exit code is the same value we placed in the register, that means its register a opcode. We found it, '\x08\xa0\x08' (imm a 10) and '\x10\x80\x80', exit code was 10.  
  - Now, i had 4 remaining syscall whose opcode were to be find yet. open, read_code, read_mem, and write for 4 values 01, 02, 20, 80. Remember remaining codes we found to be unknowsn syscall, exit and sleep
  - For open, I was sure the return value was ff for file not found. So, i checked exit status with different syscall opcodes.**01 is open() opcode**
  - Now, bruetforced for STK operaation, setting "/flag" string on stack and calling open() and then exit(). If open returned a valid fd, we guess the STK opcode ie; 40
  - I guessed register c by settung different values in remaining register opcodes. and one of it returned the same value. That was a hint that the returneed values indicates the corresponding register which contains this value.
  - So, for reminig 3 syacll opcodes, i observed that on 80 and 02, the program continuos ans the status was S (sleep), that means both are trying to read from stdin. So i tried to input some garbage "A"*88 affter the program waits. The program returned 88. That gave a surety that, it read 88 bytes. I was sure it was read(). And the remaing opcode ie; 20 was for write() obviously. THAT WAS ALL I NEEDED TO READ THE FLAGG :yum:
```
082f08 #imm a '/'
000840 # stk 0 a; push a 
086608 #imm a 'f'
000840 # stk 0 a; push a 
086c08 #imm a 'l'
000840 # stk 0 a; push a 
086108 #imm a 'a' 
000840 # stk 0 a; push a 
086708 # imm a 'g'
000840 # stk 0 a; push a

080108 # imm a 01 ie; stack offset
010880 # open , return value in a

01ff08 # imm c ff ie; no of bytes to read
020880 # read 

080108 # imm a 01 ie; stdout
200880 # write
100880 # exit
```




