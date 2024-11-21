//===--- ModernizeTidyModule.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "AvoidBindCheck.h"
#include "AvoidCArraysCheck.h"
#include "ConcatNestedNamespacesCheck.h"
#include "DeprecatedHeadersCheck.h"
#include "DeprecatedIosBaseAliasesCheck.h"
#include "LoopConvertCheck.h"
#include "MacroToEnumCheck.h"
#include "MakeSharedCheck.h"
#include "MakeUniqueCheck.h"
#include "MinMaxUseInitializerListCheck.h"
#include "PassByValueCheck.h"
#include "RawStringLiteralCheck.h"
#include "RedundantVoidArgCheck.h"
#include "ReplaceAutoPtrCheck.h"
#include "ReplaceDisallowCopyAndAssignMacroCheck.h"
#include "ReplaceRandomShuffleCheck.h"
#include "ReturnBracedInitListCheck.h"
#include "ShrinkToFitCheck.h"
#include "TypeTraitsCheck.h"
#include "UnaryStaticAssertCheck.h"
#include "UseAutoCheck.h"
#include "UseBoolLiteralsCheck.h"
#include "UseConstraintsCheck.h"
#include "UseDefaultMemberInitCheck.h"
#include "UseDesignatedInitializersCheck.h"
#include "UseEmplaceCheck.h"
#include "UseEqualsDefaultCheck.h"
#include "UseEqualsDeleteCheck.h"
#include "UseNodiscardCheck.h"
#include "UseNoexceptCheck.h"
#include "UseNullptrCheck.h"
#include "UseOverrideCheck.h"
#include "UseRangesCheck.h"
#include "UseStartsEndsWithCheck.h"
#include "UseStdFormatCheck.h"
#include "UseStdNumbersCheck.h"
#include "UseStdPrintCheck.h"
#include "UseTrailingReturnTypeCheck.h"
#include "UseTransparentFunctorsCheck.h"
#include "UseUncaughtExceptionsCheck.h"
#include "UseUsingCheck.h"

using namespace clang::ast_matchers;

namespace clang::tidy {
namespace modernize {

class ModernizeModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidBindCheck, "modernize-avoid-bind");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidCArraysCheck,
                              "modernize-avoid-c-arrays");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ConcatNestedNamespacesCheck, 
        "modernize-concat-nested-namespaces");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DeprecatedHeadersCheck, 
        "modernize-deprecated-headers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DeprecatedIosBaseAliasesCheck, 
        "modernize-deprecated-ios-base-aliases");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, LoopConvertCheck, "modernize-loop-convert");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MacroToEnumCheck, "modernize-macro-to-enum");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MakeSharedCheck, "modernize-make-shared");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MakeUniqueCheck, "modernize-make-unique");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MinMaxUseInitializerListCheck, 
        "modernize-min-max-use-initializer-list");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, PassByValueCheck, "modernize-pass-by-value");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseDesignatedInitializersCheck, 
        "modernize-use-designated-initializers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseRangesCheck, "modernize-use-ranges");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseStartsEndsWithCheck, 
        "modernize-use-starts-ends-with");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseStdFormatCheck, "modernize-use-std-format");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseStdNumbersCheck, 
        "modernize-use-std-numbers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseStdPrintCheck, "modernize-use-std-print");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RawStringLiteralCheck, 
        "modernize-raw-string-literal");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantVoidArgCheck, 
        "modernize-redundant-void-arg");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReplaceAutoPtrCheck, 
        "modernize-replace-auto-ptr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReplaceDisallowCopyAndAssignMacroCheck, 
        "modernize-replace-disallow-copy-and-assign-macro");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReplaceRandomShuffleCheck, 
        "modernize-replace-random-shuffle");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReturnBracedInitListCheck, 
        "modernize-return-braced-init-list");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ShrinkToFitCheck, "modernize-shrink-to-fit");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TypeTraitsCheck, "modernize-type-traits");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnaryStaticAssertCheck, 
        "modernize-unary-static-assert");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseAutoCheck, "modernize-use-auto");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseBoolLiteralsCheck, 
        "modernize-use-bool-literals");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseConstraintsCheck, 
        "modernize-use-constraints");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseDefaultMemberInitCheck, 
        "modernize-use-default-member-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseEmplaceCheck, "modernize-use-emplace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseEqualsDefaultCheck, "modernize-use-equals-default");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseEqualsDeleteCheck, 
        "modernize-use-equals-delete");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseNodiscardCheck, 
        "modernize-use-nodiscard");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseNoexceptCheck, "modernize-use-noexcept");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseNullptrCheck, "modernize-use-nullptr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseOverrideCheck, "modernize-use-override");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseTrailingReturnTypeCheck, 
        "modernize-use-trailing-return-type");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseTransparentFunctorsCheck, 
        "modernize-use-transparent-functors");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseUncaughtExceptionsCheck, 
        "modernize-use-uncaught-exceptions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseUsingCheck, "modernize-use-using");
  }
};

// Register the ModernizeTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<ModernizeModule> X("modernize-module",
                                                       "Add modernize checks.");

} // namespace modernize

// This anchor is used to force the linker to link in the generated object file
// and thus register the ModernizeModule.
volatile int ModernizeModuleAnchorSource = 0;

} // namespace clang::tidy
