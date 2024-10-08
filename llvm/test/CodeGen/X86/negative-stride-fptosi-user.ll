; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-- | FileCheck %s

; LSR previously eliminated the sitofp by introducing an induction
; variable which stepped by a bogus ((double)UINT32_C(-1)). It's theoretically
; possible to eliminate the sitofp using a proper -1.0 step though; this
; test should be changed if that is done.

define void @foo(i32 %N) nounwind {
; CHECK-LABEL: foo:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    testl %edi, %edi
; CHECK-NEXT:    js .LBB0_1
; CHECK-NEXT:  # %bb.4: # %return
; CHECK-NEXT:    retq
; CHECK-NEXT:  .LBB0_1: # %bb.preheader
; CHECK-NEXT:    pushq %rbp
; CHECK-NEXT:    pushq %rbx
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movl %edi, %ebx
; CHECK-NEXT:    xorl %ebp, %ebp
; CHECK-NEXT:    .p2align 4
; CHECK-NEXT:  .LBB0_2: # %bb
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    xorps %xmm0, %xmm0
; CHECK-NEXT:    cvtsi2sd %ebp, %xmm0
; CHECK-NEXT:    callq bar@PLT
; CHECK-NEXT:    decl %ebp
; CHECK-NEXT:    cmpl %ebp, %ebx
; CHECK-NEXT:    jne .LBB0_2
; CHECK-NEXT:  # %bb.3:
; CHECK-NEXT:    addq $8, %rsp
; CHECK-NEXT:    popq %rbx
; CHECK-NEXT:    popq %rbp
; CHECK-NEXT:    retq
entry:
  %0 = icmp slt i32 %N, 0                         ; <i1> [#uses=1]
  br i1 %0, label %bb, label %return

bb:                                               ; preds = %bb, %entry
  %i.03 = phi i32 [ 0, %entry ], [ %2, %bb ]      ; <i32> [#uses=2]
  %1 = sitofp i32 %i.03 to double                  ; <double> [#uses=1]
  tail call void @bar(double %1) nounwind
  %2 = add nsw i32 %i.03, -1                       ; <i32> [#uses=2]
  %exitcond = icmp eq i32 %2, %N                  ; <i1> [#uses=1]
  br i1 %exitcond, label %return, label %bb

return:                                           ; preds = %bb, %entry
  ret void
}

declare void @bar(double)
