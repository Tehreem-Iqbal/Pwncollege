.global _start

_start:
	.intel_syntax noprefix
	mov rax, 0
	mov r10, 0
	cmp rdi, 0
	jne av
	je gh
av:
	mov r9, r10
	inc r10
	cmp [rdi+r9], rax
	jne av
dec r10
mov rax, r10
gh:
	inc r9

	
    
	 
	