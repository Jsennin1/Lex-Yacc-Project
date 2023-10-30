 .section .rodata
.Lprompt: .string"> "
.Lread: .string"%ld"
.Lprint: .string"%ld\n"
 .text
.global main
main:
 pushq %rbp
 movq %rsp,%rbp
 subq $16,%rsp
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
 pushq -8(%rbp)
 pushq $1
 popq %rdx
 popq %rax
 addq %rdx,%rax
 pushq %rax
 popq -8(%rbp)
 pushq -8(%rbp)
 pushq -16(%rbp)
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
 imulq %rdx
 pushq %rax
 popq %rsi
 movq $.Lprint,%rdi
 movq $0,%rax
 call printf
 leave
 ret
