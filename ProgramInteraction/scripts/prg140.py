from pwn import *
p = process(["bash", "my_script.sh"])
for i in range(7):
    print(p.recvline())

for i in range(5):
    print(p.recvline())
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
print(p.recvline())
print(p.recvline())
print(p.recvline())

