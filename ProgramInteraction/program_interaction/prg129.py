from pwn import *
fd10, fd11 = os.pipe()
fd20, fd21 = os.pipe()
if(os.fork()==0):
    p = process("/bin/cat")
    os.close(fd20)
    os.close(fd21)
    os.close(fd10)
    os.dup2(fd11,1)
if(os.fork() == 0):
    os.close(fd11)
    os.close(fd20)
    os.dup2(fd10,0)
    os.dup2(fd21,1)
    p = process("/challenge/embryoio_level134")
    for i in range(28):
        print(p.recvline())
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
if(os.fork()==0):
    os.close(fd10)
    os.close(fd11)
    os.close(fd21)
    os.dup2(fd20,0)
    p = process("/bin/cat")
else:
    os.wait()

