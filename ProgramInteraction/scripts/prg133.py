from pwn import *
p = process("/challenge/embryoio_level133")
for i in range(16):
    print(p.recvline())
lane = str(p.recvline())
print(lane)
lane = lane[10:]
#print(lane)
#print("-----------------------------------------")
pid = lane[lane.find('PID'):lane.find(')')]
pid = pid[4:]
#print(pid)
lane = lane[lane.find('[')+1:lane.find(']')]
print(lane)
for i in range(500):
    lane2 = lane.split(',')[i]
    #print(lane2)
    lane2 = lane2[lane2.find('S'):-1]
    print(i, "   ",lane2)
    os.kill(int(pid), signal.Signals[lane2].value)
    print(p.recvline())
print(p.recvuntil('}'))