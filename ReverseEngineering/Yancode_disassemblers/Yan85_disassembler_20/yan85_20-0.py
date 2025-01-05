from pwn import *

yan85 = process('/challenge/babyrev-level-20-0')
#48982F7653B643507F856BC4F2919C4533119659DD
key = bytes.fromhex('48982F7653B643507F856BC4F2919C4533119659DD7677787980')
yan85.send(key)
#print(yan85.recvuntil(b'INCORRECT!'))
output = yan85.recvall()

print(output.decode('utf-8', errors='ignore'))