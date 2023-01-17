from pwn import *
p = process("./client")
while(True):
    line = p.recvline()
    print(line)
    line = line.decode(encoding="utf_8")
    lane = line[line.find(':')+2:-1]
    sol = eval(lane)
    print(sol)
    p.sendline(str(sol))
    #print(p.recvline())
    