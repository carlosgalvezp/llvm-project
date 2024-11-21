//===--- BugproneTidyModule.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../cppcoreguidelines/NarrowingConversionsCheck.h"
#include "ArgumentCommentCheck.h"
#include "AssertSideEffectCheck.h"
#include "AssignmentInIfConditionCheck.h"
#include "BadSignalToKillThreadCheck.h"
#include "BitwisePointerCastCheck.h"
#include "BoolPointerImplicitConversionCheck.h"
#include "BranchCloneCheck.h"
#include "CastingThroughVoidCheck.h"
#include "ChainedComparisonCheck.h"
#include "ComparePointerToMemberVirtualFunctionCheck.h"
#include "CopyConstructorInitCheck.h"
#include "CrtpConstructorAccessibilityCheck.h"
#include "DanglingHandleCheck.h"
#include "DynamicStaticInitializersCheck.h"
#include "EasilySwappableParametersCheck.h"
#include "EmptyCatchCheck.h"
#include "ExceptionEscapeCheck.h"
#include "FoldInitTypeCheck.h"
#include "ForwardDeclarationNamespaceCheck.h"
#include "ForwardingReferenceOverloadCheck.h"
#include "ImplicitWideningOfMultiplicationResultCheck.h"
#include "InaccurateEraseCheck.h"
#include "IncDecInConditionsCheck.h"
#include "IncorrectEnableIfCheck.h"
#include "IncorrectRoundingsCheck.h"
#include "InfiniteLoopCheck.h"
#include "IntegerDivisionCheck.h"
#include "LambdaFunctionNameCheck.h"
#include "MacroParenthesesCheck.h"
#include "MacroRepeatedSideEffectsCheck.h"
#include "MisplacedOperatorInStrlenInAllocCheck.h"
#include "MisplacedPointerArithmeticInAllocCheck.h"
#include "MisplacedWideningCastCheck.h"
#include "MoveForwardingReferenceCheck.h"
#include "MultiLevelImplicitPointerConversionCheck.h"
#include "MultipleNewInOneExpressionCheck.h"
#include "MultipleStatementMacroCheck.h"
#include "NoEscapeCheck.h"
#include "NonZeroEnumToBoolConversionCheck.h"
#include "NondeterministicPointerIterationOrderCheck.h"
#include "NotNullTerminatedResultCheck.h"
#include "OptionalValueConversionCheck.h"
#include "ParentVirtualCallCheck.h"
#include "PointerArithmeticOnPolymorphicObjectCheck.h"
#include "PosixReturnCheck.h"
#include "RedundantBranchConditionCheck.h"
#include "ReservedIdentifierCheck.h"
#include "ReturnConstRefFromParameterCheck.h"
#include "SharedPtrArrayMismatchCheck.h"
#include "SignalHandlerCheck.h"
#include "SignedCharMisuseCheck.h"
#include "SizeofContainerCheck.h"
#include "SizeofExpressionCheck.h"
#include "SpuriouslyWakeUpFunctionsCheck.h"
#include "StandaloneEmptyCheck.h"
#include "StringConstructorCheck.h"
#include "StringIntegerAssignmentCheck.h"
#include "StringLiteralWithEmbeddedNulCheck.h"
#include "StringviewNullptrCheck.h"
#include "SuspiciousEnumUsageCheck.h"
#include "SuspiciousIncludeCheck.h"
#include "SuspiciousMemoryComparisonCheck.h"
#include "SuspiciousMemsetUsageCheck.h"
#include "SuspiciousMissingCommaCheck.h"
#include "SuspiciousReallocUsageCheck.h"
#include "SuspiciousSemicolonCheck.h"
#include "SuspiciousStringCompareCheck.h"
#include "SuspiciousStringviewDataUsageCheck.h"
#include "SwappedArgumentsCheck.h"
#include "SwitchMissingDefaultCaseCheck.h"
#include "TaggedUnionMemberCountCheck.h"
#include "TerminatingContinueCheck.h"
#include "ThrowKeywordMissingCheck.h"
#include "TooSmallLoopVariableCheck.h"
#include "UncheckedOptionalAccessCheck.h"
#include "UndefinedMemoryManipulationCheck.h"
#include "UndelegatedConstructorCheck.h"
#include "UnhandledExceptionAtNewCheck.h"
#include "UnhandledSelfAssignmentCheck.h"
#include "UniquePtrArrayMismatchCheck.h"
#include "UnsafeFunctionsCheck.h"
#include "UnusedLocalNonTrivialVariableCheck.h"
#include "UnusedRaiiCheck.h"
#include "UnusedReturnValueCheck.h"
#include "UseAfterMoveCheck.h"
#include "VirtualNearMissCheck.h"

namespace clang::tidy {
namespace bugprone {

class BugproneModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ArgumentCommentCheck, 
        "bugprone-argument-comment");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AssertSideEffectCheck, 
        "bugprone-assert-side-effect");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AssignmentInIfConditionCheck, 
        "bugprone-assignment-in-if-condition");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, BadSignalToKillThreadCheck, 
        "bugprone-bad-signal-to-kill-thread");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, BitwisePointerCastCheck, 
        "bugprone-bitwise-pointer-cast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, BoolPointerImplicitConversionCheck, 
        "bugprone-bool-pointer-implicit-conversion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, BranchCloneCheck, "bugprone-branch-clone");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, CastingThroughVoidCheck, 
        "bugprone-casting-through-void");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ChainedComparisonCheck, 
        "bugprone-chained-comparison");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ComparePointerToMemberVirtualFunctionCheck, 
        "bugprone-compare-pointer-to-member-virtual-function");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, CopyConstructorInitCheck, 
        "bugprone-copy-constructor-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DanglingHandleCheck, 
        "bugprone-dangling-handle");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DynamicStaticInitializersCheck, 
        "bugprone-dynamic-static-initializers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, EasilySwappableParametersCheck, 
        "bugprone-easily-swappable-parameters");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, EmptyCatchCheck, "bugprone-empty-catch");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ExceptionEscapeCheck, 
        "bugprone-exception-escape");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, FoldInitTypeCheck, "bugprone-fold-init-type");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ForwardDeclarationNamespaceCheck, 
        "bugprone-forward-declaration-namespace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ForwardingReferenceOverloadCheck, 
        "bugprone-forwarding-reference-overload");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ImplicitWideningOfMultiplicationResultCheck, 
        "bugprone-implicit-widening-of-multiplication-result");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InaccurateEraseCheck, 
        "bugprone-inaccurate-erase");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IncorrectEnableIfCheck, 
        "bugprone-incorrect-enable-if");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReturnConstRefFromParameterCheck, 
        "bugprone-return-const-ref-from-parameter");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SwitchMissingDefaultCaseCheck, 
        "bugprone-switch-missing-default-case");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IncDecInConditionsCheck, 
        "bugprone-inc-dec-in-conditions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IncorrectRoundingsCheck, 
        "bugprone-incorrect-roundings");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InfiniteLoopCheck, "bugprone-infinite-loop");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IntegerDivisionCheck, 
        "bugprone-integer-division");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, LambdaFunctionNameCheck, 
        "bugprone-lambda-function-name");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MacroParenthesesCheck, 
        "bugprone-macro-parentheses");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MacroRepeatedSideEffectsCheck, 
        "bugprone-macro-repeated-side-effects");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisplacedOperatorInStrlenInAllocCheck, 
        "bugprone-misplaced-operator-in-strlen-in-alloc");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisplacedPointerArithmeticInAllocCheck, 
        "bugprone-misplaced-pointer-arithmetic-in-alloc");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisplacedWideningCastCheck, 
        "bugprone-misplaced-widening-cast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MoveForwardingReferenceCheck, 
        "bugprone-move-forwarding-reference");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MultiLevelImplicitPointerConversionCheck, 
        "bugprone-multi-level-implicit-pointer-conversion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MultipleNewInOneExpressionCheck, 
        "bugprone-multiple-new-in-one-expression");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MultipleStatementMacroCheck, 
        "bugprone-multiple-statement-macro");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NondeterministicPointerIterationOrderCheck,
        "bugprone-nondeterministic-pointer-iteration-order");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, OptionalValueConversionCheck,
        "bugprone-optional-value-conversion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, PointerArithmeticOnPolymorphicObjectCheck, 
        "bugprone-pointer-arithmetic-on-polymorphic-object");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantBranchConditionCheck, 
        "bugprone-redundant-branch-condition");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::NarrowingConversionsCheck, 
        "bugprone-narrowing-conversions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoEscapeCheck, "bugprone-no-escape");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NonZeroEnumToBoolConversionCheck, 
        "bugprone-non-zero-enum-to-bool-conversion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NotNullTerminatedResultCheck, 
        "bugprone-not-null-terminated-result");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ParentVirtualCallCheck, 
        "bugprone-parent-virtual-call");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, PosixReturnCheck, "bugprone-posix-return");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReservedIdentifierCheck, 
        "bugprone-reserved-identifier");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SharedPtrArrayMismatchCheck, 
        "bugprone-shared-ptr-array-mismatch");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SignalHandlerCheck, "bugprone-signal-handler");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SignedCharMisuseCheck, 
        "bugprone-signed-char-misuse");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SizeofContainerCheck, 
        "bugprone-sizeof-container");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SizeofExpressionCheck, 
        "bugprone-sizeof-expression");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SpuriouslyWakeUpFunctionsCheck, 
        "bugprone-spuriously-wake-up-functions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StandaloneEmptyCheck, 
        "bugprone-standalone-empty");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StringConstructorCheck, 
        "bugprone-string-constructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StringIntegerAssignmentCheck, 
        "bugprone-string-integer-assignment");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StringLiteralWithEmbeddedNulCheck, 
        "bugprone-string-literal-with-embedded-nul");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StringviewNullptrCheck, 
        "bugprone-stringview-nullptr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousEnumUsageCheck, 
        "bugprone-suspicious-enum-usage");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousIncludeCheck, 
        "bugprone-suspicious-include");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousMemoryComparisonCheck, 
        "bugprone-suspicious-memory-comparison");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousMemsetUsageCheck, 
        "bugprone-suspicious-memset-usage");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousMissingCommaCheck, 
        "bugprone-suspicious-missing-comma");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousReallocUsageCheck, 
        "bugprone-suspicious-realloc-usage");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousSemicolonCheck, 
        "bugprone-suspicious-semicolon");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousStringCompareCheck, 
        "bugprone-suspicious-string-compare");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousStringviewDataUsageCheck, 
        "bugprone-suspicious-stringview-data-usage");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SwappedArgumentsCheck, 
        "bugprone-swapped-arguments");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TaggedUnionMemberCountCheck, 
        "bugprone-tagged-union-member-count");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TerminatingContinueCheck, 
        "bugprone-terminating-continue");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ThrowKeywordMissingCheck, 
        "bugprone-throw-keyword-missing");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TooSmallLoopVariableCheck, 
        "bugprone-too-small-loop-variable");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UncheckedOptionalAccessCheck, 
        "bugprone-unchecked-optional-access");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UndefinedMemoryManipulationCheck, 
        "bugprone-undefined-memory-manipulation");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UndelegatedConstructorCheck, 
        "bugprone-undelegated-constructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnhandledSelfAssignmentCheck, 
        "bugprone-unhandled-self-assignment");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnhandledExceptionAtNewCheck, 
        "bugprone-unhandled-exception-at-new");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UniquePtrArrayMismatchCheck, 
        "bugprone-unique-ptr-array-mismatch");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, CrtpConstructorAccessibilityCheck, 
        "bugprone-crtp-constructor-accessibility");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnsafeFunctionsCheck, 
        "bugprone-unsafe-functions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedLocalNonTrivialVariableCheck, 
        "bugprone-unused-local-non-trivial-variable");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedRaiiCheck, "bugprone-unused-raii");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedReturnValueCheck, 
        "bugprone-unused-return-value");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseAfterMoveCheck, "bugprone-use-after-move");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, VirtualNearMissCheck, 
        "bugprone-virtual-near-miss");
  }
};

} // namespace bugprone

// Register the BugproneTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<bugprone::BugproneModule>
    X("bugprone-module", "Adds checks for bugprone code constructs.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the BugproneModule.
volatile int BugproneModuleAnchorSource = 0;

} // namespace clang::tidy
