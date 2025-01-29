from pwn import *

pty = process.PTY
p = process("./a.out", stdin=pty, stdout=pty)
for i in range(21):
    print(p.recvline())
lane = str(p.recvline())
#print(lane)
lane = lane[10:]
#print(lane)
#print("-----------------------------------------")
pid = lane[lane.find('PID'):lane.find(')')]
pid = pid[4:]
#print(pid)
#print("-----------------------------------------")
lane = lane[lane.find('[')+1:lane.find(']')]
print(lane)
for i in range(500):
    lane2 = lane.split(',')[i]
    #print(lane2)
    lane2 = lane2[lane2.find('S'):-1]
    print(lane2)
    print(i,"-----------------------------------------")
    os.kill(int(pid), signal.Signals[lane2].value)
    print(p.recvline())
print(p.recvuntil('}'))