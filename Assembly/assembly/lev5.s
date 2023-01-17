.global _start

_start:
	.intel_syntax noprefix
    mov rcx, 0x403000
    mov r9, 0 
    mov r11, rdi 
    cmp r11, 0     
    je end
while:
    mov r10, [r11]
    cmp r10, 0
    je end
    cmp r10, 90
    jg gr

    mov rdi, r10
    call rcx
    mov r10, rax
    inc r9
gr:
    inc r11
    jmp while
end:
    mov rax, r9
    ret
