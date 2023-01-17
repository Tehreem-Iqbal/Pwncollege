	.file	"c01.c"
	.text
	.section	.rodata
.LC0:
	.string	"/bin/sh"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %edx
	movl	$0, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	execve@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 11.3.0-3) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
