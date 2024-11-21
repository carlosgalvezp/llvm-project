//===-- CppCoreGuidelinesTidyModule.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../misc/NonPrivateMemberVariablesInClassesCheck.h"
#include "../misc/UnconventionalAssignOperatorCheck.h"
#include "../modernize/AvoidCArraysCheck.h"
#include "../modernize/MacroToEnumCheck.h"
#include "../modernize/UseDefaultMemberInitCheck.h"
#include "../modernize/UseOverrideCheck.h"
#include "../performance/NoexceptDestructorCheck.h"
#include "../performance/NoexceptMoveConstructorCheck.h"
#include "../performance/NoexceptSwapCheck.h"
#include "../readability/MagicNumbersCheck.h"
#include "AvoidCapturingLambdaCoroutinesCheck.h"
#include "AvoidConstOrRefDataMembersCheck.h"
#include "AvoidDoWhileCheck.h"
#include "AvoidGotoCheck.h"
#include "AvoidNonConstGlobalVariablesCheck.h"
#include "AvoidReferenceCoroutineParametersCheck.h"
#include "InitVariablesCheck.h"
#include "InterfacesGlobalInitCheck.h"
#include "MacroUsageCheck.h"
#include "MisleadingCaptureDefaultByValueCheck.h"
#include "MissingStdForwardCheck.h"
#include "NarrowingConversionsCheck.h"
#include "NoMallocCheck.h"
#include "NoSuspendWithLockCheck.h"
#include "OwningMemoryCheck.h"
#include "PreferMemberInitializerCheck.h"
#include "ProBoundsArrayToPointerDecayCheck.h"
#include "ProBoundsConstantArrayIndexCheck.h"
#include "ProBoundsPointerArithmeticCheck.h"
#include "ProTypeConstCastCheck.h"
#include "ProTypeCstyleCastCheck.h"
#include "ProTypeMemberInitCheck.h"
#include "ProTypeReinterpretCastCheck.h"
#include "ProTypeStaticCastDowncastCheck.h"
#include "ProTypeUnionAccessCheck.h"
#include "ProTypeVarargCheck.h"
#include "RvalueReferenceParamNotMovedCheck.h"
#include "SlicingCheck.h"
#include "SpecialMemberFunctionsCheck.h"
#include "VirtualClassDestructorCheck.h"

namespace clang::tidy {
namespace cppcoreguidelines {

/// A module containing checks of the C++ Core Guidelines
class CppCoreGuidelinesModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidCapturingLambdaCoroutinesCheck, 
        "cppcoreguidelines-avoid-capturing-lambda-coroutines");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::AvoidCArraysCheck,
                              "cppcoreguidelines-avoid-c-arrays");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidConstOrRefDataMembersCheck, 
        "cppcoreguidelines-avoid-const-or-ref-data-members");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidDoWhileCheck, 
        "cppcoreguidelines-avoid-do-while");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidGotoCheck, 
        "cppcoreguidelines-avoid-goto");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::MagicNumbersCheck, 
        "cppcoreguidelines-avoid-magic-numbers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidNonConstGlobalVariablesCheck, 
        "cppcoreguidelines-avoid-non-const-global-variables");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidReferenceCoroutineParametersCheck, 
        "cppcoreguidelines-avoid-reference-coroutine-parameters");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseOverrideCheck, 
        "cppcoreguidelines-explicit-virtual-functions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InitVariablesCheck, 
        "cppcoreguidelines-init-variables");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InterfacesGlobalInitCheck, 
        "cppcoreguidelines-interfaces-global-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::MacroToEnumCheck, 
        "cppcoreguidelines-macro-to-enum");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MacroUsageCheck, 
        "cppcoreguidelines-macro-usage");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisleadingCaptureDefaultByValueCheck, 
        "cppcoreguidelines-misleading-capture-default-by-value");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MissingStdForwardCheck, 
        "cppcoreguidelines-missing-std-forward");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NarrowingConversionsCheck, 
        "cppcoreguidelines-narrowing-conversions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoMallocCheck, "cppcoreguidelines-no-malloc");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoSuspendWithLockCheck, 
        "cppcoreguidelines-no-suspend-with-lock");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::NoexceptDestructorCheck, 
        "cppcoreguidelines-noexcept-destructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::NoexceptMoveConstructorCheck, 
        "cppcoreguidelines-noexcept-move-operations");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::NoexceptSwapCheck, 
        "cppcoreguidelines-noexcept-swap");
    CLANG_TIDY_REGISTER_CHECK(
        CheckFactories, misc::NonPrivateMemberVariablesInClassesCheck,
        "cppcoreguidelines-non-private-member-variables-in-classes");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, OwningMemoryCheck, 
        "cppcoreguidelines-owning-memory");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, PreferMemberInitializerCheck, 
        "cppcoreguidelines-prefer-member-initializer");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProBoundsArrayToPointerDecayCheck, 
        "cppcoreguidelines-pro-bounds-array-to-pointer-decay");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProBoundsConstantArrayIndexCheck, 
        "cppcoreguidelines-pro-bounds-constant-array-index");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProBoundsPointerArithmeticCheck, 
        "cppcoreguidelines-pro-bounds-pointer-arithmetic");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeConstCastCheck, 
        "cppcoreguidelines-pro-type-const-cast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeCstyleCastCheck, 
        "cppcoreguidelines-pro-type-cstyle-cast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeMemberInitCheck, 
        "cppcoreguidelines-pro-type-member-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeReinterpretCastCheck, 
        "cppcoreguidelines-pro-type-reinterpret-cast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeStaticCastDowncastCheck, 
        "cppcoreguidelines-pro-type-static-cast-downcast");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeUnionAccessCheck, 
        "cppcoreguidelines-pro-type-union-access");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProTypeVarargCheck, 
        "cppcoreguidelines-pro-type-vararg");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RvalueReferenceParamNotMovedCheck, 
        "cppcoreguidelines-rvalue-reference-param-not-moved");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SpecialMemberFunctionsCheck, 
        "cppcoreguidelines-special-member-functions");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SlicingCheck, "cppcoreguidelines-slicing");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, modernize::UseDefaultMemberInitCheck, 
        "cppcoreguidelines-use-default-member-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::UnconventionalAssignOperatorCheck, 
        "cppcoreguidelines-c-copy-assignment-signature");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, VirtualClassDestructorCheck, 
        "cppcoreguidelines-virtual-class-destructor");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    ClangTidyOptions::OptionMap &Opts = Options.CheckOptions;

    Opts["cppcoreguidelines-non-private-member-variables-in-classes."
         "IgnoreClassesWithAllMemberVariablesBeingPublic"] = "true";

    return Options;
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<CppCoreGuidelinesModule>
    X("cppcoreguidelines-module", "Adds checks for the C++ Core Guidelines.");

} // namespace cppcoreguidelines

// This anchor is used to force the linker to link in the generated object file
// and thus register the CppCoreGuidelinesModule.
volatile int CppCoreGuidelinesModuleAnchorSource = 0;

} // namespace clang::tidy
