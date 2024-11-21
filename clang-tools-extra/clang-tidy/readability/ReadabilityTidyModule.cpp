//===--- ReadabilityTidyModule.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "AvoidConstParamsInDecls.h"
#include "AvoidNestedConditionalOperatorCheck.h"
#include "AvoidReturnWithVoidValueCheck.h"
#include "AvoidUnconditionalPreprocessorIfCheck.h"
#include "BracesAroundStatementsCheck.h"
#include "ConstReturnTypeCheck.h"
#include "ContainerContainsCheck.h"
#include "ContainerDataPointerCheck.h"
#include "ContainerSizeEmptyCheck.h"
#include "ConvertMemberFunctionsToStatic.h"
#include "DeleteNullPointerCheck.h"
#include "DuplicateIncludeCheck.h"
#include "ElseAfterReturnCheck.h"
#include "EnumInitialValueCheck.h"
#include "FunctionCognitiveComplexityCheck.h"
#include "FunctionSizeCheck.h"
#include "IdentifierLengthCheck.h"
#include "IdentifierNamingCheck.h"
#include "ImplicitBoolConversionCheck.h"
#include "InconsistentDeclarationParameterNameCheck.h"
#include "IsolateDeclarationCheck.h"
#include "MagicNumbersCheck.h"
#include "MakeMemberFunctionConstCheck.h"
#include "MathMissingParenthesesCheck.h"
#include "MisleadingIndentationCheck.h"
#include "MisplacedArrayIndexCheck.h"
#include "NamedParameterCheck.h"
#include "NonConstParameterCheck.h"
#include "OperatorsRepresentationCheck.h"
#include "QualifiedAutoCheck.h"
#include "RedundantAccessSpecifiersCheck.h"
#include "RedundantCastingCheck.h"
#include "RedundantControlFlowCheck.h"
#include "RedundantDeclarationCheck.h"
#include "RedundantFunctionPtrDereferenceCheck.h"
#include "RedundantInlineSpecifierCheck.h"
#include "RedundantMemberInitCheck.h"
#include "RedundantPreprocessorCheck.h"
#include "RedundantSmartptrGetCheck.h"
#include "RedundantStringCStrCheck.h"
#include "RedundantStringInitCheck.h"
#include "ReferenceToConstructedTemporaryCheck.h"
#include "SimplifyBooleanExprCheck.h"
#include "SimplifySubscriptExprCheck.h"
#include "StaticAccessedThroughInstanceCheck.h"
#include "StaticDefinitionInAnonymousNamespaceCheck.h"
#include "StringCompareCheck.h"
#include "SuspiciousCallArgumentCheck.h"
#include "UniqueptrDeleteReleaseCheck.h"
#include "UppercaseLiteralSuffixCheck.h"
#include "UseAnyOfAllOfCheck.h"
#include "UseStdMinMaxCheck.h"

namespace clang::tidy {
namespace readability {

class ReadabilityModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidConstParamsInDecls, 
        "readability-avoid-const-params-in-decls");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidNestedConditionalOperatorCheck, 
        "readability-avoid-nested-conditional-operator");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidReturnWithVoidValueCheck, 
        "readability-avoid-return-with-void-value");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidUnconditionalPreprocessorIfCheck, 
        "readability-avoid-unconditional-preprocessor-if");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, BracesAroundStatementsCheck, 
        "readability-braces-around-statements");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ConstReturnTypeCheck, 
        "readability-const-return-type");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ContainerContainsCheck, 
        "readability-container-contains");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ContainerDataPointerCheck, 
        "readability-container-data-pointer");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ContainerSizeEmptyCheck, 
        "readability-container-size-empty");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ConvertMemberFunctionsToStatic, 
        "readability-convert-member-functions-to-static");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DeleteNullPointerCheck, 
        "readability-delete-null-pointer");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DuplicateIncludeCheck, 
        "readability-duplicate-include");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ElseAfterReturnCheck, 
        "readability-else-after-return");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, EnumInitialValueCheck, 
        "readability-enum-initial-value");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, FunctionCognitiveComplexityCheck, 
        "readability-function-cognitive-complexity");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, FunctionSizeCheck, 
        "readability-function-size");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IdentifierLengthCheck, 
        "readability-identifier-length");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IdentifierNamingCheck, 
        "readability-identifier-naming");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ImplicitBoolConversionCheck, 
        "readability-implicit-bool-conversion");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MathMissingParenthesesCheck, 
        "readability-math-missing-parentheses");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantInlineSpecifierCheck, 
        "readability-redundant-inline-specifier");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InconsistentDeclarationParameterNameCheck, 
        "readability-inconsistent-declaration-parameter-name");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, IsolateDeclarationCheck, 
        "readability-isolate-declaration");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MagicNumbersCheck, 
        "readability-magic-numbers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MakeMemberFunctionConstCheck, 
        "readability-make-member-function-const");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisleadingIndentationCheck, 
        "readability-misleading-indentation");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MisplacedArrayIndexCheck, 
        "readability-misplaced-array-index");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, OperatorsRepresentationCheck, 
        "readability-operators-representation");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, QualifiedAutoCheck, 
        "readability-qualified-auto");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantAccessSpecifiersCheck, 
        "readability-redundant-access-specifiers");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantCastingCheck, 
        "readability-redundant-casting");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantFunctionPtrDereferenceCheck, 
        "readability-redundant-function-ptr-dereference");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantMemberInitCheck, 
        "readability-redundant-member-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantPreprocessorCheck, 
        "readability-redundant-preprocessor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ReferenceToConstructedTemporaryCheck, 
        "readability-reference-to-constructed-temporary");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SimplifySubscriptExprCheck, 
        "readability-simplify-subscript-expr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StaticAccessedThroughInstanceCheck, 
        "readability-static-accessed-through-instance");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StaticDefinitionInAnonymousNamespaceCheck, 
        "readability-static-definition-in-anonymous-namespace");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StringCompareCheck, 
        "readability-string-compare");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::NamedParameterCheck, 
        "readability-named-parameter");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NonConstParameterCheck, 
        "readability-non-const-parameter");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantControlFlowCheck, 
        "readability-redundant-control-flow");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantDeclarationCheck, 
        "readability-redundant-declaration");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantSmartptrGetCheck, 
        "readability-redundant-smartptr-get");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantStringCStrCheck, 
        "readability-redundant-string-cstr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, RedundantStringInitCheck, 
        "readability-redundant-string-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SimplifyBooleanExprCheck, 
        "readability-simplify-boolean-expr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SuspiciousCallArgumentCheck, 
        "readability-suspicious-call-argument");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UniqueptrDeleteReleaseCheck, 
        "readability-uniqueptr-delete-release");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UppercaseLiteralSuffixCheck, 
        "readability-uppercase-literal-suffix");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseAnyOfAllOfCheck, 
        "readability-use-anyofallof");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UseStdMinMaxCheck, 
        "readability-use-std-min-max");
  }
};

// Register the ReadabilityModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<ReadabilityModule>
    X("readability-module", "Adds readability-related checks.");

} // namespace readability

// This anchor is used to force the linker to link in the generated object file
// and thus register the ReadabilityModule.
volatile int ReadabilityModuleAnchorSource = 0;

} // namespace clang::tidy
