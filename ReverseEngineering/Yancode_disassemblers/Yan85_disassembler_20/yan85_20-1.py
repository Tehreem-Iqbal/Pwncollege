from pwn import *

yan85 = process('/challenge/babyrev-level-20-1')
#48982F7653B643507F856BC4F2919C4533119659DD
key = bytes.fromhex('3AC711768B2F5419817C8A9C5BC65103BE456FA613628A723B1FE947')
yan85.send(key)
#print(yan85.recvuntil(b'INCORRECT!'))
output = yan85.recvall()

print(output.decode('utf-8', errors='ignore'))