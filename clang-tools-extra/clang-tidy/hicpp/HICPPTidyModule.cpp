//===------- HICPPTidyModule.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../bugprone/UndelegatedConstructorCheck.h"
#include "../bugprone/UseAfterMoveCheck.h"
#include "../cppcoreguidelines/AvoidGotoCheck.h"
#include "../cppcoreguidelines/NoMallocCheck.h"
#include "../cppcoreguidelines/ProBoundsArrayToPointerDecayCheck.h"
#include "../cppcoreguidelines/ProTypeMemberInitCheck.h"
#include "../cppcoreguidelines/ProTypeVarargCheck.h"
#include "../cppcoreguidelines/SpecialMemberFunctionsCheck.h"
#include "../google/DefaultArgumentsCheck.h"
#include "../google/ExplicitConstructorCheck.h"
#include "../misc/NewDeleteOverloadsCheck.h"
#include "../misc/StaticAssertCheck.h"
#include "../modernize/AvoidCArraysCheck.h"
#include "../modernize/DeprecatedHeadersCheck.h"
#include "../modernize/UseAutoCheck.h"
#include "../modernize/UseEmplaceCheck.h"
#include "../modernize/UseEqualsDefaultCheck.h"
#include "../modernize/UseEqualsDeleteCheck.h"
#include "../modernize/UseNoexceptCheck.h"
#include "../modernize/UseNullptrCheck.h"
#include "../modernize/UseOverrideCheck.h"
#include "../performance/MoveConstArgCheck.h"
#include "../performance/NoexceptMoveConstructorCheck.h"
#include "../readability/BracesAroundStatementsCheck.h"
#include "../readability/FunctionSizeCheck.h"
#include "../readability/NamedParameterCheck.h"
#include "../readability/UppercaseLiteralSuffixCheck.h"
#include "ExceptionBaseclassCheck.h"
#include "IgnoredRemoveResultCheck.h"
#include "MultiwayPathsCoveredCheck.h"
#include "NoAssemblerCheck.h"
#include "SignedBitwiseCheck.h"

namespace clang::tidy {
namespace hicpp {

class HICPPModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::AvoidCArraysCheck,
                              "hicpp-avoid-c-arrays");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::AvoidGotoCheck, 
        "hicpp-avoid-goto");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::BracesAroundStatementsCheck, 
        "hicpp-braces-around-statements");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::DeprecatedHeadersCheck, 
        "hicpp-deprecated-headers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ExceptionBaseclassCheck, 
        "hicpp-exception-baseclass");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IgnoredRemoveResultCheck, 
        "hicpp-ignored-remove-result");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MultiwayPathsCoveredCheck, 
        "hicpp-multiway-paths-covered");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SignedBitwiseCheck, "hicpp-signed-bitwise");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, google::ExplicitConstructorCheck, 
        "hicpp-explicit-conversions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::FunctionSizeCheck, 
        "hicpp-function-size");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::NamedParameterCheck, 
        "hicpp-named-parameter");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UseAfterMoveCheck, 
        "hicpp-invalid-access-moved");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::ProTypeMemberInitCheck, 
        "hicpp-member-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::MoveConstArgCheck, 
        "hicpp-move-const-arg");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::NewDeleteOverloadsCheck, 
        "hicpp-new-delete-operators");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::NoexceptMoveConstructorCheck, 
        "hicpp-noexcept-move");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::ProBoundsArrayToPointerDecayCheck,
            "hicpp-no-array-decay");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoAssemblerCheck, "hicpp-no-assembler");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::NoMallocCheck, 
        "hicpp-no-malloc");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::SpecialMemberFunctionsCheck,
            "hicpp-special-member-functions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::StaticAssertCheck, 
        "hicpp-static-assert");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseAutoCheck, "hicpp-use-auto");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UndelegatedConstructorCheck, 
        "hicpp-undelegated-constructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseEmplaceCheck, 
        "hicpp-use-emplace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseEqualsDefaultCheck, 
        "hicpp-use-equals-default");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseEqualsDeleteCheck, 
        "hicpp-use-equals-delete");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseNoexceptCheck, 
        "hicpp-use-noexcept");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseNullptrCheck, 
        "hicpp-use-nullptr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseOverrideCheck, 
        "hicpp-use-override");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::UppercaseLiteralSuffixCheck, 
        "hicpp-uppercase-literal-suffix");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, cppcoreguidelines::ProTypeVarargCheck, 
        "hicpp-vararg");
  }
};

// Register the HICPPModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<HICPPModule>
    X("hicpp-module", "Adds High-Integrity C++ checks.");

} // namespace hicpp

// This anchor is used to force the linker to link in the generated object file
// and thus register the HICPPModule.
volatile int HICPPModuleAnchorSource = 0;

} // namespace clang::tidy
