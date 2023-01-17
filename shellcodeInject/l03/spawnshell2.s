.global _start

_start:
	.intel_syntax noprefix
	xor rcx, rcx
	push 0x68732f2f
	push 0x6e69622f
	mov rbx, rsp
	mov al, 59
	syscall
