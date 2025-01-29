from pwn import *
p = process("./a.out")
for i in range(14):
    print(p.recvline())
for i in range(500):
    lane = str(p.recvline().strip())
    print(lane)
    print("=========================")
    lane1 = lane[lane.find(':')+2:-1]
    print(lane1)
    print("=========================")
    sol = eval(lane1)
    print(sol)
    print("=========================")
    p.sendline(str(sol))
    print(p.recvline())
print(p.recvuntil('}'))
