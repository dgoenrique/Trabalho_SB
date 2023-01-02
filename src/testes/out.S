.section .rodata
.data
.text

f2:
pushq %rbp
movq %rsp, %rbp
ponteiro = %rdi

Definição da função

Definição das variáveis
.align 4
vi11: .int 0
vi1: -4
.align 4
vi22: .int 0
vi2: -8
.align 4
va3: .int 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
va3: -128
subq $128, %rsp



movl $1, vi1


movl vi1, %edi
movl $va3, %rsi
call f1
movl %eax, vi2


movl $5, %edi
movl pa1, %esi
call f1
movl %eax, vi2


movl vi1, %ecx
movl %ecx, vi2


movl pi1, %ecx
movl vi2, %r10d
addl %ecx, %r10d
movl %r10d, vi1


movl vi1, %ecx
movl $-5, %r10d
imull %ecx, %r10d
movl %r10d, vi2


Definição do set das variáveis de um vetor
movq $va2, %r8
movq $5, %r9
imulq $4, %r9
addq %r8, %r9
movq $2, (%r9)

Definição do set das variáveis de um vetor
movq $pa2, %r8
movq $0, %r9
imulq $4, %r9
addq %r8, %r9
movl vi1, %r10d
movslq %r10d, (%r9)

Definição do get das variáveis de um vetor
movq $va2, %r8
movq $8, %r9
imulq $4, %r9
addq %r8, %r9
movl (%r9), %r10d
movl %r10d, vi1

Definição de if
cmpl $0, vi1
jne end_if

movl $0, vi1


end_if:

Definição de if
cmpl $0, vi1
jne end_if

Definição do get das variáveis de um vetor
movq $va2, %r8
movq $8, %r9
imulq $4, %r9
addq %r8, %r9
movl (%r9), %r10d
movl %r10d, vi1

end_if:

Definição de if
cmpl $0, vi1
jne end_if

Definição do retorno
movl vi1, %eax


end_if:

Definição do retorno
movl vi2, %eax


Definição do fim
leave
ret

