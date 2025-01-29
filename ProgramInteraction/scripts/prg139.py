from pwn import *
#p = process("./a.out")
#p = process(["cat | ./a.out | cat"])
p = os.system("cat | ./a.out | cat")
for i in range(32):
    print(i)
    print(os.read(sys.stdin, 1000))
'''
for i in range(50):
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
'''