//===--- GoogleTidyModule.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../readability/BracesAroundStatementsCheck.h"
#include "../readability/FunctionSizeCheck.h"
#include "../readability/NamespaceCommentCheck.h"
#include "AvoidCStyleCastsCheck.h"
#include "AvoidNSObjectNewCheck.h"
#include "AvoidThrowingObjCExceptionCheck.h"
#include "AvoidUnderscoreInGoogletestNameCheck.h"
#include "DefaultArgumentsCheck.h"
#include "ExplicitConstructorCheck.h"
#include "ExplicitMakePairCheck.h"
#include "FunctionNamingCheck.h"
#include "GlobalNamesInHeadersCheck.h"
#include "GlobalVariableDeclarationCheck.h"
#include "IntegerTypesCheck.h"
#include "OverloadedUnaryAndCheck.h"
#include "TodoCommentCheck.h"
#include "UnnamedNamespaceInHeaderCheck.h"
#include "UpgradeGoogletestCaseCheck.h"
#include "UsingNamespaceDirectiveCheck.h"

using namespace clang::ast_matchers;

namespace clang::tidy {
namespace google {

class GoogleModule : public ClangTidyModule {
 public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, build::ExplicitMakePairCheck, 
        "google-build-explicit-make-pair");

    CLANG_TIDY_REGISTER_CHECK(CheckFactories, build::UnnamedNamespaceInHeaderCheck, 
        "google-build-namespaces");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, build::UsingNamespaceDirectiveCheck, 
        "google-build-using-namespace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DefaultArgumentsCheck, 
        "google-default-arguments");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ExplicitConstructorCheck, 
        "google-explicit-constructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::GlobalNamesInHeadersCheck, 
        "google-global-names-in-headers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, objc::AvoidNSObjectNewCheck, 
        "google-objc-avoid-nsobject-new");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, objc::AvoidThrowingObjCExceptionCheck, 
        "google-objc-avoid-throwing-exception");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, objc::FunctionNamingCheck, 
        "google-objc-function-naming");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, objc::GlobalVariableDeclarationCheck, 
        "google-objc-global-variable-declaration");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, runtime::IntegerTypesCheck, 
        "google-runtime-int");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, runtime::OverloadedUnaryAndCheck, 
        "google-runtime-operator");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::AvoidUnderscoreInGoogletestNameCheck,
            "google-readability-avoid-underscore-in-googletest-name");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::AvoidCStyleCastsCheck, 
        "google-readability-casting");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::TodoCommentCheck, 
        "google-readability-todo");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, clang::tidy::readability::BracesAroundStatementsCheck,
            "google-readability-braces-around-statements");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, clang::tidy::readability::FunctionSizeCheck, 
        "google-readability-function-size");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, clang::tidy::readability::NamespaceCommentCheck,
            "google-readability-namespace-comments");

/*
    CheckName: "google-readability-namespace-comments" -> module = "google"
    Check->getName(): "readability-NamespaceCommentCheck" -> module = "readability" 

    if module(ChekName) == module(Check->getName()) -> it's primary check

    but if a check is moved from a folder to another, it's easy to miss to update the name
    of the module.

    Current approach of detecting colon doesn't work if there are multiple namespaces, like
    in google checks.

*/
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UpgradeGoogletestCaseCheck, 
        "google-upgrade-googletest-case");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    auto &Opts = Options.CheckOptions;
    Opts["google-readability-braces-around-statements.ShortStatementLines"] =
        "1";
    Opts["google-readability-function-size.StatementThreshold"] = "800";
    Opts["google-readability-namespace-comments.ShortNamespaceLines"] = "10";
    Opts["google-readability-namespace-comments.SpacesBeforeComments"] = "2";
    return Options;
  }
};

// Register the GoogleTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<GoogleModule> X("google-module",
                                                    "Adds Google lint checks.");

}  // namespace google

// This anchor is used to force the linker to link in the generated object file
// and thus register the GoogleModule.
volatile int GoogleModuleAnchorSource = 0;

} // namespace clang::tidy
