 .file "test1.c"
 .text
 .globl func
 .type func, @function
func:
.LFB0:
 .cfi_startproc
 pushq %rbp
 .cfi_def_cfa_offset 16
 .cfi_offset 6, -16
 movq %rsp, %rbp
 .cfi_def_cfa_register 6
 subq $16, %rsp
 movl %edi, -4(%rbp)
 movl %esi, -8(%rbp)
 movl %edx, -12(%rbp)
 movl -12(%rbp), %eax
 movl -8(%rbp), %edx
 addl %eax, %edx
 movl -4(%rbp), %eax
 movl %edx, %esi
 movl %eax, %edi
 call func2
 leave
 .cfi_def_cfa 7, 8
 ret
 .cfi_endproc
.LFE0:
 .size func, .-func
 .ident "GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
 .section .note.GNU-stack,"",@progbits