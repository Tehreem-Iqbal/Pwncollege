#!/usr/lib/python3

from pwn import *
import os
import signal

pty = process.PTY
proc = process("./a.out")
for i in range(20):
    print(proc.recvline())
for i in range(500):
    proc.recvuntil("solution for:")
    out = proc.recvline();
    str_out = str(out)

    exp = str_out[3:len(str_out)-3]
    print(i, "------------------------")
    proc.sendline(str(eval(exp)))
print(proc.recvuntil("}"))
