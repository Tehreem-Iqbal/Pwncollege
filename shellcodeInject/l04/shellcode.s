.global _start
_start:
	.intel_syntax noprefix
	mov eax, 2               
	mov rdi, 0x67616c662f               
	mov esi, 0               
	syscall               
	mov edi, 1                
	mov esi, eax               
	mov edx, 0                
	mov eax, 40                
	syscall                
	mov eax, 60               
	syscall                

