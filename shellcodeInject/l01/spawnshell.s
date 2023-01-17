.global _start
_start:
	.intel_syntax noprefix
	xor rax, rax
        mov al, 59
	mov r10, abc
	mov r11, [abc]
	lea r10, abc
        lea rdi, [rip+abc]              
        xor rsi, rsi
abc:
	.string "A"              
        xor rdx, rdx
        syscall          



