from pwn import *

yan85 = process('babyrev-level-21-0')
#48982F7653B643507F856BC4F2919C4533119659DD
output = yan85.recvuntil('yancode:')
print(output)
print("Sending vmcode bytes to execute")
key = bytes.fromhex('402f10406640406C0840612040670180100080400080080080200080010040011040004040000808200840001010201040664040ff08082001400110082020')
yan85.send(key)
print("Data sent")
#output = yan85.recvall()
for i in range(100):
    print(yan85.recvline())

#print(output.decode('utf-8', errors='ignore'))
