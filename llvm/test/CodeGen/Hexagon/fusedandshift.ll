; RUN: llc -mtriple=hexagon -hexagon-extract=0 -hexbit-extract=0 < %s | FileCheck %s
; Check that we generate fused logical and with shift instruction.
; Disable "extract" generation, since it may eliminate the and/lsr.

; CHECK: r{{[0-9]+}} = and(#15,lsr(r{{[0-9]+}},#{{[0-9]+}})

define i32 @main(ptr %a, ptr %b) nounwind {
  entry:
  %0 = load i16, ptr %a, align 2
  %conv1 = sext i16 %0 to i32
  %shr1 = ashr i32 %conv1, 3
  %and1 = and i32 %shr1, 15
  %conv2 = trunc i32 %and1 to i16
  store i16 %conv2, ptr %b, align 2
  ret i32 0
}

