; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 5
; RUN: llc -mtriple=i386-pc-windows-msvc < %s -o - | FileCheck -check-prefix=MSVC-X86 %s
; RUN: llc -mtriple=x86_64-pc-windows-msvc < %s -o - | FileCheck -check-prefix=MSVC-X64 %s

; Make sure fastisel falls back and does something secure.
; RUN: llc -mtriple=i686-pc-windows-msvc -O0 < %s -o - | FileCheck -check-prefix=MSVC-X86-O0 %s
; RUN: llc -mtriple=x86_64-pc-windows-msvc -O0 < %s -o - | FileCheck -check-prefix=MSVC-X64-O0 %s

@"\01LC" = internal constant [11 x i8] c"buf == %s\0A\00"    ; <ptr> [#uses=1]

define void @test(ptr %a) nounwind ssp {
; MSVC-X86-LABEL: test:
; MSVC-X86:       # %bb.0: # %entry
; MSVC-X86-NEXT:    pushl %esi
; MSVC-X86-NEXT:    subl $12, %esp
; MSVC-X86-NEXT:    movl ___security_cookie, %eax
; MSVC-X86-NEXT:    xorl %esp, %eax
; MSVC-X86-NEXT:    movl %eax, {{[0-9]+}}(%esp)
; MSVC-X86-NEXT:    movl %esp, %esi
; MSVC-X86-NEXT:    pushl {{[0-9]+}}(%esp)
; MSVC-X86-NEXT:    pushl %esi
; MSVC-X86-NEXT:    calll _strcpy
; MSVC-X86-NEXT:    addl $8, %esp
; MSVC-X86-NEXT:    pushl %esi
; MSVC-X86-NEXT:    pushl $LC
; MSVC-X86-NEXT:    calll _printf
; MSVC-X86-NEXT:    addl $8, %esp
; MSVC-X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; MSVC-X86-NEXT:    xorl %esp, %eax
; MSVC-X86-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-NEXT:    cmpl %eax, %ecx
; MSVC-X86-NEXT:    jne LBB0_2
; MSVC-X86-NEXT:  # %bb.1: # %return
; MSVC-X86-NEXT:    addl $12, %esp
; MSVC-X86-NEXT:    popl %esi
; MSVC-X86-NEXT:    retl
; MSVC-X86-NEXT:  LBB0_2: # %return
; MSVC-X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; MSVC-X86-NEXT:    xorl %esp, %ecx
; MSVC-X86-NEXT:    calll @__security_check_cookie@4
;
; MSVC-X64-LABEL: test:
; MSVC-X64:       # %bb.0: # %entry
; MSVC-X64-NEXT:    pushq %rsi
; MSVC-X64-NEXT:    subq $64, %rsp
; MSVC-X64-NEXT:    movq %rcx, %rdx
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-NEXT:    xorq %rsp, %rax
; MSVC-X64-NEXT:    movq %rax, {{[0-9]+}}(%rsp)
; MSVC-X64-NEXT:    movq %rcx, {{[0-9]+}}(%rsp)
; MSVC-X64-NEXT:    leaq {{[0-9]+}}(%rsp), %rsi
; MSVC-X64-NEXT:    movq %rsi, %rcx
; MSVC-X64-NEXT:    callq strcpy
; MSVC-X64-NEXT:    leaq LC(%rip), %rcx
; MSVC-X64-NEXT:    movq %rsi, %rdx
; MSVC-X64-NEXT:    callq printf
; MSVC-X64-NEXT:    movq {{[0-9]+}}(%rsp), %rax
; MSVC-X64-NEXT:    xorq %rsp, %rax
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rcx
; MSVC-X64-NEXT:    cmpq %rax, %rcx
; MSVC-X64-NEXT:    jne .LBB0_2
; MSVC-X64-NEXT:  # %bb.1: # %return
; MSVC-X64-NEXT:    addq $64, %rsp
; MSVC-X64-NEXT:    popq %rsi
; MSVC-X64-NEXT:    retq
; MSVC-X64-NEXT:  .LBB0_2: # %return
; MSVC-X64-NEXT:    movq {{[0-9]+}}(%rsp), %rcx
; MSVC-X64-NEXT:    xorq %rsp, %rcx
; MSVC-X64-NEXT:    callq __security_check_cookie
;
; MSVC-X86-O0-LABEL: test:
; MSVC-X86-O0:       # %bb.0: # %entry
; MSVC-X86-O0-NEXT:    subl $20, %esp
; MSVC-X86-O0-NEXT:    movl {{[0-9]+}}(%esp), %eax
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %eax
; MSVC-X86-O0-NEXT:    xorl %esp, %eax
; MSVC-X86-O0-NEXT:    movl %eax, {{[0-9]+}}(%esp)
; MSVC-X86-O0-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; MSVC-X86-O0-NEXT:    movl %esp, %eax
; MSVC-X86-O0-NEXT:    movl %ecx, 4(%eax)
; MSVC-X86-O0-NEXT:    leal {{[0-9]+}}(%esp), %ecx
; MSVC-X86-O0-NEXT:    movl %ecx, (%eax)
; MSVC-X86-O0-NEXT:    calll _strcpy
; MSVC-X86-O0-NEXT:    leal LC, %ecx
; MSVC-X86-O0-NEXT:    leal {{[0-9]+}}(%esp), %eax
; MSVC-X86-O0-NEXT:    movl %ecx, (%esp)
; MSVC-X86-O0-NEXT:    movl %eax, {{[0-9]+}}(%esp)
; MSVC-X86-O0-NEXT:    calll _printf
; MSVC-X86-O0-NEXT:  # %bb.1: # %return
; MSVC-X86-O0-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; MSVC-X86-O0-NEXT:    xorl %esp, %ecx
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %eax
; MSVC-X86-O0-NEXT:    subl %ecx, %eax
; MSVC-X86-O0-NEXT:    jne LBB0_3
; MSVC-X86-O0-NEXT:    jmp LBB0_2
; MSVC-X86-O0-NEXT:  LBB0_3: # %return
; MSVC-X86-O0-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; MSVC-X86-O0-NEXT:    xorl %esp, %ecx
; MSVC-X86-O0-NEXT:    calll @__security_check_cookie@4
; MSVC-X86-O0-NEXT:  LBB0_2: # %return
; MSVC-X86-O0-NEXT:    addl $20, %esp
; MSVC-X86-O0-NEXT:    retl
;
; MSVC-X64-O0-LABEL: test:
; MSVC-X64-O0:       # %bb.0: # %entry
; MSVC-X64-O0-NEXT:    subq $56, %rsp
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    xorq %rsp, %rax
; MSVC-X64-O0-NEXT:    movq %rax, {{[0-9]+}}(%rsp)
; MSVC-X64-O0-NEXT:    movq %rcx, {{[0-9]+}}(%rsp)
; MSVC-X64-O0-NEXT:    movq {{[0-9]+}}(%rsp), %rdx
; MSVC-X64-O0-NEXT:    leaq {{[0-9]+}}(%rsp), %rcx
; MSVC-X64-O0-NEXT:    callq strcpy
; MSVC-X64-O0-NEXT:    leaq LC(%rip), %rcx
; MSVC-X64-O0-NEXT:    leaq {{[0-9]+}}(%rsp), %rdx
; MSVC-X64-O0-NEXT:    callq printf
; MSVC-X64-O0-NEXT:  # %bb.1: # %return
; MSVC-X64-O0-NEXT:    movq {{[0-9]+}}(%rsp), %rcx
; MSVC-X64-O0-NEXT:    xorq %rsp, %rcx
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    subq %rcx, %rax
; MSVC-X64-O0-NEXT:    jne .LBB0_3
; MSVC-X64-O0-NEXT:    jmp .LBB0_2
; MSVC-X64-O0-NEXT:  .LBB0_3: # %return
; MSVC-X64-O0-NEXT:    movq {{[0-9]+}}(%rsp), %rcx
; MSVC-X64-O0-NEXT:    xorq %rsp, %rcx
; MSVC-X64-O0-NEXT:    callq __security_check_cookie
; MSVC-X64-O0-NEXT:  .LBB0_2: # %return
; MSVC-X64-O0-NEXT:    addq $56, %rsp
; MSVC-X64-O0-NEXT:    retq

entry:
 %a_addr = alloca ptr    ; <ptr> [#uses=2]
 %buf = alloca [8 x i8]    ; <ptr> [#uses=2]
 store ptr %a, ptr %a_addr
 %0 = load ptr, ptr %a_addr, align 4    ; <ptr> [#uses=1]
 %1 = call ptr @strcpy(ptr %buf, ptr %0) nounwind   ; <ptr> [#uses=0]
 %2 = call i32 (ptr, ...) @printf(ptr @"\01LC", ptr %buf) nounwind    ; <i32> [#uses=0]
 br label %return

return:    ; preds = %entry
 ret void
}

declare void @escape(ptr)

define void @test_vla(i32 %n) nounwind ssp {
; MSVC-X86-LABEL: test_vla:
; MSVC-X86:       # %bb.0:
; MSVC-X86-NEXT:    pushl %ebp
; MSVC-X86-NEXT:    movl %esp, %ebp
; MSVC-X86-NEXT:    pushl %eax
; MSVC-X86-NEXT:    movl 8(%ebp), %eax
; MSVC-X86-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-NEXT:    xorl %ebp, %ecx
; MSVC-X86-NEXT:    movl %ecx, -4(%ebp)
; MSVC-X86-NEXT:    shll $2, %eax
; MSVC-X86-NEXT:    calll __chkstk
; MSVC-X86-NEXT:    movl %esp, %eax
; MSVC-X86-NEXT:    pushl %eax
; MSVC-X86-NEXT:    calll _escape
; MSVC-X86-NEXT:    addl $4, %esp
; MSVC-X86-NEXT:    movl -4(%ebp), %eax
; MSVC-X86-NEXT:    xorl %ebp, %eax
; MSVC-X86-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-NEXT:    cmpl %eax, %ecx
; MSVC-X86-NEXT:    jne LBB1_2
; MSVC-X86-NEXT:  # %bb.1:
; MSVC-X86-NEXT:    movl %ebp, %esp
; MSVC-X86-NEXT:    popl %ebp
; MSVC-X86-NEXT:    retl
; MSVC-X86-NEXT:  LBB1_2:
; MSVC-X86-NEXT:    movl -4(%ebp), %ecx
; MSVC-X86-NEXT:    xorl %ebp, %ecx
; MSVC-X86-NEXT:    calll @__security_check_cookie@4
;
; MSVC-X64-LABEL: test_vla:
; MSVC-X64:       # %bb.0:
; MSVC-X64-NEXT:    pushq %rbp
; MSVC-X64-NEXT:    subq $16, %rsp
; MSVC-X64-NEXT:    leaq {{[0-9]+}}(%rsp), %rbp
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-NEXT:    xorq %rbp, %rax
; MSVC-X64-NEXT:    movq %rax, -8(%rbp)
; MSVC-X64-NEXT:    movl %ecx, %eax
; MSVC-X64-NEXT:    leaq 15(,%rax,4), %rax
; MSVC-X64-NEXT:    andq $-16, %rax
; MSVC-X64-NEXT:    callq __chkstk
; MSVC-X64-NEXT:    subq %rax, %rsp
; MSVC-X64-NEXT:    movq %rsp, %rcx
; MSVC-X64-NEXT:    subq $32, %rsp
; MSVC-X64-NEXT:    callq escape
; MSVC-X64-NEXT:    addq $32, %rsp
; MSVC-X64-NEXT:    movq -8(%rbp), %rax
; MSVC-X64-NEXT:    xorq %rbp, %rax
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rcx
; MSVC-X64-NEXT:    cmpq %rax, %rcx
; MSVC-X64-NEXT:    jne .LBB1_2
; MSVC-X64-NEXT:  # %bb.1:
; MSVC-X64-NEXT:    movq %rbp, %rsp
; MSVC-X64-NEXT:    popq %rbp
; MSVC-X64-NEXT:    retq
; MSVC-X64-NEXT:  .LBB1_2:
; MSVC-X64-NEXT:    movq -8(%rbp), %rcx
; MSVC-X64-NEXT:    xorq %rbp, %rcx
; MSVC-X64-NEXT:    subq $32, %rsp
; MSVC-X64-NEXT:    callq __security_check_cookie
;
; MSVC-X86-O0-LABEL: test_vla:
; MSVC-X86-O0:       # %bb.0:
; MSVC-X86-O0-NEXT:    pushl %ebp
; MSVC-X86-O0-NEXT:    movl %esp, %ebp
; MSVC-X86-O0-NEXT:    pushl %eax
; MSVC-X86-O0-NEXT:    movl 8(%ebp), %eax
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    movl %ecx, -4(%ebp)
; MSVC-X86-O0-NEXT:    shll $2, %eax
; MSVC-X86-O0-NEXT:    calll __chkstk
; MSVC-X86-O0-NEXT:    movl %esp, %eax
; MSVC-X86-O0-NEXT:    subl $4, %esp
; MSVC-X86-O0-NEXT:    movl %eax, (%esp)
; MSVC-X86-O0-NEXT:    calll _escape
; MSVC-X86-O0-NEXT:    addl $4, %esp
; MSVC-X86-O0-NEXT:    movl -4(%ebp), %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %eax
; MSVC-X86-O0-NEXT:    subl %ecx, %eax
; MSVC-X86-O0-NEXT:    jne LBB1_2
; MSVC-X86-O0-NEXT:    jmp LBB1_1
; MSVC-X86-O0-NEXT:  LBB1_2:
; MSVC-X86-O0-NEXT:    movl -4(%ebp), %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    calll @__security_check_cookie@4
; MSVC-X86-O0-NEXT:  LBB1_1:
; MSVC-X86-O0-NEXT:    movl %ebp, %esp
; MSVC-X86-O0-NEXT:    popl %ebp
; MSVC-X86-O0-NEXT:    retl
;
; MSVC-X64-O0-LABEL: test_vla:
; MSVC-X64-O0:       # %bb.0:
; MSVC-X64-O0-NEXT:    pushq %rbp
; MSVC-X64-O0-NEXT:    subq $16, %rsp
; MSVC-X64-O0-NEXT:    leaq {{[0-9]+}}(%rsp), %rbp
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    xorq %rbp, %rax
; MSVC-X64-O0-NEXT:    movq %rax, -8(%rbp)
; MSVC-X64-O0-NEXT:    movl %ecx, %eax
; MSVC-X64-O0-NEXT:    # kill: def $rax killed $eax
; MSVC-X64-O0-NEXT:    leaq 15(,%rax,4), %rax
; MSVC-X64-O0-NEXT:    andq $-16, %rax
; MSVC-X64-O0-NEXT:    callq __chkstk
; MSVC-X64-O0-NEXT:    subq %rax, %rsp
; MSVC-X64-O0-NEXT:    movq %rsp, %rcx
; MSVC-X64-O0-NEXT:    subq $32, %rsp
; MSVC-X64-O0-NEXT:    callq escape
; MSVC-X64-O0-NEXT:    addq $32, %rsp
; MSVC-X64-O0-NEXT:    movq -8(%rbp), %rcx
; MSVC-X64-O0-NEXT:    xorq %rbp, %rcx
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    subq %rcx, %rax
; MSVC-X64-O0-NEXT:    jne .LBB1_2
; MSVC-X64-O0-NEXT:    jmp .LBB1_1
; MSVC-X64-O0-NEXT:  .LBB1_2:
; MSVC-X64-O0-NEXT:    movq -8(%rbp), %rcx
; MSVC-X64-O0-NEXT:    xorq %rbp, %rcx
; MSVC-X64-O0-NEXT:    subq $32, %rsp
; MSVC-X64-O0-NEXT:    callq __security_check_cookie
; MSVC-X64-O0-NEXT:  .LBB1_1:
; MSVC-X64-O0-NEXT:    movq %rbp, %rsp
; MSVC-X64-O0-NEXT:    popq %rbp
; MSVC-X64-O0-NEXT:    retq
  %vla = alloca i32, i32 %n
  call void @escape(ptr %vla)
  ret void
}

; This case is interesting because we address local variables with RBX but XOR
; the guard value with RBP. That's fine, either value will do, as long as they
; are the same across the life of the frame.

define void @test_vla_realign(i32 %n) nounwind ssp {
; MSVC-X86-LABEL: test_vla_realign:
; MSVC-X86:       # %bb.0:
; MSVC-X86-NEXT:    pushl %ebp
; MSVC-X86-NEXT:    movl %esp, %ebp
; MSVC-X86-NEXT:    pushl %edi
; MSVC-X86-NEXT:    pushl %esi
; MSVC-X86-NEXT:    andl $-32, %esp
; MSVC-X86-NEXT:    subl $32, %esp
; MSVC-X86-NEXT:    movl %esp, %esi
; MSVC-X86-NEXT:    movl 8(%ebp), %eax
; MSVC-X86-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-NEXT:    xorl %ebp, %ecx
; MSVC-X86-NEXT:    movl %ecx, 12(%esi)
; MSVC-X86-NEXT:    shll $2, %eax
; MSVC-X86-NEXT:    calll __chkstk
; MSVC-X86-NEXT:    movl %esp, %edi
; MSVC-X86-NEXT:    movl %esi, %eax
; MSVC-X86-NEXT:    pushl %eax
; MSVC-X86-NEXT:    calll _escape
; MSVC-X86-NEXT:    addl $4, %esp
; MSVC-X86-NEXT:    pushl %edi
; MSVC-X86-NEXT:    calll _escape
; MSVC-X86-NEXT:    addl $4, %esp
; MSVC-X86-NEXT:    movl 12(%esi), %eax
; MSVC-X86-NEXT:    xorl %ebp, %eax
; MSVC-X86-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-NEXT:    cmpl %eax, %ecx
; MSVC-X86-NEXT:    jne LBB2_2
; MSVC-X86-NEXT:  # %bb.1:
; MSVC-X86-NEXT:    leal -8(%ebp), %esp
; MSVC-X86-NEXT:    popl %esi
; MSVC-X86-NEXT:    popl %edi
; MSVC-X86-NEXT:    popl %ebp
; MSVC-X86-NEXT:    retl
; MSVC-X86-NEXT:  LBB2_2:
; MSVC-X86-NEXT:    movl 12(%esi), %ecx
; MSVC-X86-NEXT:    xorl %ebp, %ecx
; MSVC-X86-NEXT:    calll @__security_check_cookie@4
;
; MSVC-X64-LABEL: test_vla_realign:
; MSVC-X64:       # %bb.0:
; MSVC-X64-NEXT:    pushq %rbp
; MSVC-X64-NEXT:    pushq %rsi
; MSVC-X64-NEXT:    pushq %rbx
; MSVC-X64-NEXT:    subq $32, %rsp
; MSVC-X64-NEXT:    leaq {{[0-9]+}}(%rsp), %rbp
; MSVC-X64-NEXT:    andq $-32, %rsp
; MSVC-X64-NEXT:    movq %rsp, %rbx
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-NEXT:    xorq %rbp, %rax
; MSVC-X64-NEXT:    movq %rax, 24(%rbx)
; MSVC-X64-NEXT:    movl %ecx, %eax
; MSVC-X64-NEXT:    leaq 15(,%rax,4), %rax
; MSVC-X64-NEXT:    andq $-16, %rax
; MSVC-X64-NEXT:    callq __chkstk
; MSVC-X64-NEXT:    subq %rax, %rsp
; MSVC-X64-NEXT:    movq %rsp, %rsi
; MSVC-X64-NEXT:    subq $32, %rsp
; MSVC-X64-NEXT:    movq %rbx, %rcx
; MSVC-X64-NEXT:    callq escape
; MSVC-X64-NEXT:    movq %rsi, %rcx
; MSVC-X64-NEXT:    callq escape
; MSVC-X64-NEXT:    addq $32, %rsp
; MSVC-X64-NEXT:    movq 24(%rbx), %rax
; MSVC-X64-NEXT:    xorq %rbp, %rax
; MSVC-X64-NEXT:    movq __security_cookie(%rip), %rcx
; MSVC-X64-NEXT:    cmpq %rax, %rcx
; MSVC-X64-NEXT:    jne .LBB2_2
; MSVC-X64-NEXT:  # %bb.1:
; MSVC-X64-NEXT:    movq %rbp, %rsp
; MSVC-X64-NEXT:    popq %rbx
; MSVC-X64-NEXT:    popq %rsi
; MSVC-X64-NEXT:    popq %rbp
; MSVC-X64-NEXT:    retq
; MSVC-X64-NEXT:  .LBB2_2:
; MSVC-X64-NEXT:    movq 24(%rbx), %rcx
; MSVC-X64-NEXT:    xorq %rbp, %rcx
; MSVC-X64-NEXT:    subq $32, %rsp
; MSVC-X64-NEXT:    callq __security_check_cookie
;
; MSVC-X86-O0-LABEL: test_vla_realign:
; MSVC-X86-O0:       # %bb.0:
; MSVC-X86-O0-NEXT:    pushl %ebp
; MSVC-X86-O0-NEXT:    movl %esp, %ebp
; MSVC-X86-O0-NEXT:    pushl %esi
; MSVC-X86-O0-NEXT:    andl $-32, %esp
; MSVC-X86-O0-NEXT:    subl $64, %esp
; MSVC-X86-O0-NEXT:    movl %esp, %esi
; MSVC-X86-O0-NEXT:    movl 8(%ebp), %eax
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    movl %ecx, 48(%esi)
; MSVC-X86-O0-NEXT:    shll $2, %eax
; MSVC-X86-O0-NEXT:    calll __chkstk
; MSVC-X86-O0-NEXT:    movl %esp, %eax
; MSVC-X86-O0-NEXT:    movl %eax, 28(%esi) # 4-byte Spill
; MSVC-X86-O0-NEXT:    leal 32(%esi), %eax
; MSVC-X86-O0-NEXT:    subl $4, %esp
; MSVC-X86-O0-NEXT:    movl %eax, (%esp)
; MSVC-X86-O0-NEXT:    calll _escape
; MSVC-X86-O0-NEXT:    movl 28(%esi), %eax # 4-byte Reload
; MSVC-X86-O0-NEXT:    movl %eax, (%esp)
; MSVC-X86-O0-NEXT:    calll _escape
; MSVC-X86-O0-NEXT:    addl $4, %esp
; MSVC-X86-O0-NEXT:    movl 48(%esi), %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    movl ___security_cookie, %eax
; MSVC-X86-O0-NEXT:    subl %ecx, %eax
; MSVC-X86-O0-NEXT:    jne LBB2_2
; MSVC-X86-O0-NEXT:    jmp LBB2_1
; MSVC-X86-O0-NEXT:  LBB2_2:
; MSVC-X86-O0-NEXT:    movl 48(%esi), %ecx
; MSVC-X86-O0-NEXT:    xorl %ebp, %ecx
; MSVC-X86-O0-NEXT:    calll @__security_check_cookie@4
; MSVC-X86-O0-NEXT:  LBB2_1:
; MSVC-X86-O0-NEXT:    leal -4(%ebp), %esp
; MSVC-X86-O0-NEXT:    popl %esi
; MSVC-X86-O0-NEXT:    popl %ebp
; MSVC-X86-O0-NEXT:    retl
;
; MSVC-X64-O0-LABEL: test_vla_realign:
; MSVC-X64-O0:       # %bb.0:
; MSVC-X64-O0-NEXT:    pushq %rbp
; MSVC-X64-O0-NEXT:    pushq %rbx
; MSVC-X64-O0-NEXT:    subq $72, %rsp
; MSVC-X64-O0-NEXT:    leaq {{[0-9]+}}(%rsp), %rbp
; MSVC-X64-O0-NEXT:    andq $-32, %rsp
; MSVC-X64-O0-NEXT:    movq %rsp, %rbx
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    xorq %rbp, %rax
; MSVC-X64-O0-NEXT:    movq %rax, 64(%rbx)
; MSVC-X64-O0-NEXT:    movl %ecx, %eax
; MSVC-X64-O0-NEXT:    # kill: def $rax killed $eax
; MSVC-X64-O0-NEXT:    leaq 15(,%rax,4), %rax
; MSVC-X64-O0-NEXT:    andq $-16, %rax
; MSVC-X64-O0-NEXT:    callq __chkstk
; MSVC-X64-O0-NEXT:    subq %rax, %rsp
; MSVC-X64-O0-NEXT:    movq %rsp, %rax
; MSVC-X64-O0-NEXT:    movq %rax, 24(%rbx) # 8-byte Spill
; MSVC-X64-O0-NEXT:    leaq 32(%rbx), %rcx
; MSVC-X64-O0-NEXT:    subq $32, %rsp
; MSVC-X64-O0-NEXT:    callq escape
; MSVC-X64-O0-NEXT:    movq 24(%rbx), %rcx # 8-byte Reload
; MSVC-X64-O0-NEXT:    callq escape
; MSVC-X64-O0-NEXT:    addq $32, %rsp
; MSVC-X64-O0-NEXT:    movq 64(%rbx), %rcx
; MSVC-X64-O0-NEXT:    xorq %rbp, %rcx
; MSVC-X64-O0-NEXT:    movq __security_cookie(%rip), %rax
; MSVC-X64-O0-NEXT:    subq %rcx, %rax
; MSVC-X64-O0-NEXT:    jne .LBB2_2
; MSVC-X64-O0-NEXT:    jmp .LBB2_1
; MSVC-X64-O0-NEXT:  .LBB2_2:
; MSVC-X64-O0-NEXT:    movq 64(%rbx), %rcx
; MSVC-X64-O0-NEXT:    xorq %rbp, %rcx
; MSVC-X64-O0-NEXT:    subq $32, %rsp
; MSVC-X64-O0-NEXT:    callq __security_check_cookie
; MSVC-X64-O0-NEXT:  .LBB2_1:
; MSVC-X64-O0-NEXT:    leaq 8(%rbp), %rsp
; MSVC-X64-O0-NEXT:    popq %rbx
; MSVC-X64-O0-NEXT:    popq %rbp
; MSVC-X64-O0-NEXT:    retq
  %realign = alloca i32, align 32
  %vla = alloca i32, i32 %n
  call void @escape(ptr %realign)
  call void @escape(ptr %vla)
  ret void
}

declare ptr @strcpy(ptr, ptr) nounwind

declare i32 @printf(ptr, ...) nounwind

