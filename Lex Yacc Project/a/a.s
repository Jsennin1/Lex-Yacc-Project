 .section .rodata
.Lprompt: .string"> "
.Lread: .string"%ld"
.Lprint: .string"%ld\n"
 .text
.global main
main:
 pushq %rbp
 movq %rsp,%rbp
 subq $32,%rsp
 movq $.Lprompt,%rdi
 movq $0,%rax
 call printf
 leaq -8(%rbp),%rsi
 movq $.Lread,%rdi
 movq $0,%rax
 call scanf
 movq $.Lprompt,%rdi
 movq $0,%rax
 call printf
 leaq -16(%rbp),%rsi
 movq $.Lread,%rdi
 movq $0,%rax
 call scanf
 movq $.Lprompt,%rdi
 movq $0,%rax
 call printf
 leaq -24(%rbp),%rsi
 movq $.Lread,%rdi
 movq $0,%rax
 call scanf
 movq $.Lprompt,%rdi
 movq $0,%rax
 call printf
 leaq -32(%rbp),%rsi
 movq $.Lread,%rdi
 movq $0,%rax
 call scanf
 pushq -8(%rbp)
 pushq -16(%rbp)
 pushq -24(%rbp)
 popq %rdx
 popq %rax
 imulq %rdx
 pushq %rax
 pushq -32(%rbp)
 popq %rdi
 popq %rax
 movq $0,%rdx
 idivq %rdi
 pushq %rax
 popq %rdx
 popq %rax
 addq %rdx,%rax
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 pushq -8(%rbp)
 pushq -16(%rbp)
 popq %rdx
 popq %rax
 addq %rdx,%rax
 pushq %rax
 pushq -24(%rbp)
 popq %rdx
 popq %rax
 imulq %rdx
 pushq %rax
 pushq -32(%rbp)
 popq %rdi
 popq %rax
 movq $0,%rdx
 idivq %rdi
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 pushq -8(%rbp)
 pushq -16(%rbp)
 pushq -24(%rbp)
 popq %rdx
 popq %rax
 imulq %rdx
 pushq %rax
 pushq -32(%rbp)
 popq %rdi
 popq %rax
 movq $0,%rdx
 idivq %rdi
 pushq %rdx
 popq %rdx
 popq %rax
 subq %rdx,%rax
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 pushq -8(%rbp)
 pushq -16(%rbp)
 popq %rdi
 popq %rax
 movq $0,%rdx
 idivq %rdi
 pushq %rax
 pushq -24(%rbp)
 pushq -32(%rbp)
 popq %rdx
 popq %rax
 imulq %rdx
 pushq %rax
 popq %rdx
 popq %rax
 subq %rdx,%rax
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 pushq -8(%rbp)
 pushq -16(%rbp)
 popq %rdi
 popq %rax
 movq $0,%rdx
 idivq %rdi
 pushq %rdx
 pushq -24(%rbp)
 popq %rdx
 popq %rax
 addq %rdx,%rax
 pushq %rax
 pushq -32(%rbp)
 popq %rdx
 popq %rax
 subq %rdx,%rax
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 leave
 ret
