from pwn import *
import subprocess

p = process(["bash", "my_script.sh"])

for i in range(36):
  line = p.recvline()
  print(line)

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

