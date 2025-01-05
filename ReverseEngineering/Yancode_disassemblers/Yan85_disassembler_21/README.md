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

**22.0 was pretty simple to solve**


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



