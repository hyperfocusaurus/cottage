.altmacro

.macro interrupt_service_routine num
.global interrupt_service_routine_\num
interrupt_service_routine_\num:
// push 0 as the error code if the interrupt is a non-error interrupt
.if \num != 8 && \num != 10 && \num != 11 && \num != 12 && \num != 13 && \num != 14 && \num != 17 && \num != 30
    push $0
.endif

    cmpq $0x43, 16(%rsp) // if user
    jne 1f
    swapgs

1:
    push %r15
    push %r14
    push %r13
    push %r12
    push %r11
    push %r10
    push %r9
    push %r8
    push %rbp
    push %rdi
    push %rsi
    push %rdx
    push %rcx
    push %rbx
    push %rax
    mov %es, %eax
    push %rax
    mov %ds, %eax
    push %rax

    cld

    mov $0x30, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %ss

    mov $\num, %rdi
    mov $(\num * 8), %rax
    lea interrupt_table(%rip), %rbx
    add %rax, %rbx
    mov %rsp, %rsi
    xor %rbp, %rbp
    call *(%rbx)

    pop %rax
    mov %eax, %ds
    pop %rax
    mov %eax, %es
    pop %rax
    pop %rbx
    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi
    pop %rbp
    pop %r8
    pop %r9
    pop %r10
    pop %r11
    pop %r12
    pop %r13
    pop %r14
    pop %r15
    add $8, %rsp

    cmpq $0x43, 8(%rsp) // if user
    jne 1f
    swapgs

1:
    iretq
.endm

.macro serviceroutine_addr num
    .quad interrupt_service_routine_\num
.endm

.section .data

.global interrupt_service_routines
.align 8
interrupt_service_routines:
.set i,0
.rept 256
    serviceroutine_addr %i
    .set i, i+1
.endr

.section .text

.set i,0
.rept 256
    interrupt_service_routine %i
    .set i, i+1
.endr
