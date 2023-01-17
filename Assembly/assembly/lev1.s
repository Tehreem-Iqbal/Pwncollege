.global _start
_start:
	.intel_syntax noprefix
    mov eax, [rdi] 
    mov ebx, [rdi+4]
    mov ecx, [rdi+8]
    mov edx, [rdi+12]

    cmp eax, 0x7f454c46
    je ad

    cmp eax, 0x00005A4D
    je sb
    jmp ml
ad:    
    mov eax, ebx
    add eax, ecx
    add eax, edx
    jmp done
sb:
    mov eax, ebx
    sub eax, ecx
    sub eax, edx
    jmp done
ml:
    mov eax, ebx
    imul eax, ecx
    imul eax, edx
done:
    mov rbx, 765



    
