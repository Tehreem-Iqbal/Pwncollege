.global _start

_start:
	.intel_syntax noprefix
    call .str_lower
.str_lower:
        mov r9, 0
        mov r10, 0
        mov rcx, 0
        mov r11, rdi
        mov r12, 90
        mov rax, 0
        cmp r11, 0
        je end
        jne av
    av:
        mov rdx, r10
        inc r10
        cmp [r11+rdx], r12
        jle ls
        jg gr
    ls:
        mov rdi, [r11+rdx]
        call foo
        mov [r11+rdx], rax
        inc r9
    gr:
        cmp [r11+rdx], rcx
        jne av
    end:
        mov rax, r9
        ret
foo:
    mov rax, rdi
    ret

    