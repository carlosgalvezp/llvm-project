//===--- MiscTidyModule.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "ConfusableIdentifierCheck.h"
#include "ConstCorrectnessCheck.h"
#include "CoroutineHostileRAIICheck.h"
#include "DefinitionsInHeadersCheck.h"
#include "HeaderIncludeCycleCheck.h"
#include "IncludeCleanerCheck.h"
#include "MisleadingBidirectional.h"
#include "MisleadingIdentifier.h"
#include "MisplacedConstCheck.h"
#include "NewDeleteOverloadsCheck.h"
#include "NoRecursionCheck.h"
#include "NonCopyableObjects.h"
#include "NonPrivateMemberVariablesInClassesCheck.h"
#include "RedundantExpressionCheck.h"
#include "StaticAssertCheck.h"
#include "ThrowByValueCatchByReferenceCheck.h"
#include "UnconventionalAssignOperatorCheck.h"
#include "UniqueptrResetReleaseCheck.h"
#include "UnusedAliasDeclsCheck.h"
#include "UnusedParametersCheck.h"
#include "UnusedUsingDeclsCheck.h"
#include "UseAnonymousNamespaceCheck.h"
#include "UseInternalLinkageCheck.h"

namespace clang::tidy {
namespace misc {

class MiscModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ConfusableIdentifierCheck, 
        "misc-confusable-identifiers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ConstCorrectnessCheck, 
        "misc-const-correctness");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, CoroutineHostileRAIICheck, 
        "misc-coroutine-hostile-raii");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DefinitionsInHeadersCheck, 
        "misc-definitions-in-headers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, HeaderIncludeCycleCheck, 
        "misc-header-include-cycle");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IncludeCleanerCheck, "misc-include-cleaner");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisleadingBidirectionalCheck, 
        "misc-misleading-bidirectional");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisleadingIdentifierCheck, 
        "misc-misleading-identifier");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisplacedConstCheck, "misc-misplaced-const");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NewDeleteOverloadsCheck, 
        "misc-new-delete-overloads");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoRecursionCheck, "misc-no-recursion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NonCopyableObjectsCheck, 
        "misc-non-copyable-objects");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories,
                              NonPrivateMemberVariablesInClassesCheck,
                              "misc-non-private-member-variables-in-classes");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantExpressionCheck, 
        "misc-redundant-expression");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StaticAssertCheck, "misc-static-assert");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ThrowByValueCatchByReferenceCheck, 
        "misc-throw-by-value-catch-by-reference");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnconventionalAssignOperatorCheck, 
        "misc-unconventional-assign-operator");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UniqueptrResetReleaseCheck, 
        "misc-uniqueptr-reset-release");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedAliasDeclsCheck, 
        "misc-unused-alias-decls");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedParametersCheck, 
        "misc-unused-parameters");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnusedUsingDeclsCheck, 
        "misc-unused-using-decls");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseAnonymousNamespaceCheck, 
        "misc-use-anonymous-namespace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseInternalLinkageCheck, 
        "misc-use-internal-linkage");
  }
};

} // namespace misc

// Register the MiscTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misc::MiscModule>
    X("misc-module", "Adds miscellaneous lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MiscModule.
volatile int MiscModuleAnchorSource = 0;

} // namespace clang::tidy
