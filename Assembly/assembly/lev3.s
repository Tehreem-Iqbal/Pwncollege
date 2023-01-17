.global _start
_start:
	.intel_syntax noprefix
    cmp rdi, 3
    jg gr
    mov rax, 8
    mul rdi
    jmp [rsi+rax]     
gr:
    mov rax, 8
    mov rdi, 4
    mul rdi
    jmp [rsi+rax]

