//===-- PerformanceTidyModule.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "AvoidEndlCheck.h"
#include "EnumSizeCheck.h"
#include "FasterStringFindCheck.h"
#include "ForRangeCopyCheck.h"
#include "ImplicitConversionInLoopCheck.h"
#include "InefficientAlgorithmCheck.h"
#include "InefficientStringConcatenationCheck.h"
#include "InefficientVectorOperationCheck.h"
#include "MoveConstArgCheck.h"
#include "MoveConstructorInitCheck.h"
#include "NoAutomaticMoveCheck.h"
#include "NoIntToPtrCheck.h"
#include "NoexceptDestructorCheck.h"
#include "NoexceptMoveConstructorCheck.h"
#include "NoexceptSwapCheck.h"
#include "TriviallyDestructibleCheck.h"
#include "TypePromotionInMathFnCheck.h"
#include "UnnecessaryCopyInitialization.h"
#include "UnnecessaryValueParamCheck.h"

namespace clang::tidy {
namespace performance {

class PerformanceModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, AvoidEndlCheck, "performance-avoid-endl");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, EnumSizeCheck, "performance-enum-size");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, FasterStringFindCheck, 
        "performance-faster-string-find");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ForRangeCopyCheck, 
        "performance-for-range-copy");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ImplicitConversionInLoopCheck, 
        "performance-implicit-conversion-in-loop");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InefficientAlgorithmCheck, 
        "performance-inefficient-algorithm");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InefficientStringConcatenationCheck, 
        "performance-inefficient-string-concatenation");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, InefficientVectorOperationCheck, 
        "performance-inefficient-vector-operation");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MoveConstArgCheck, 
        "performance-move-const-arg");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MoveConstructorInitCheck, 
        "performance-move-constructor-init");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoAutomaticMoveCheck, 
        "performance-no-automatic-move");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoIntToPtrCheck, "performance-no-int-to-ptr");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoexceptDestructorCheck, 
        "performance-noexcept-destructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoexceptMoveConstructorCheck, 
        "performance-noexcept-move-constructor");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NoexceptSwapCheck, 
        "performance-noexcept-swap");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TriviallyDestructibleCheck, 
        "performance-trivially-destructible");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, TypePromotionInMathFnCheck, 
        "performance-type-promotion-in-math-fn");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnnecessaryCopyInitialization, 
        "performance-unnecessary-copy-initialization");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, UnnecessaryValueParamCheck, 
        "performance-unnecessary-value-param");
  }
};

// Register the PerformanceModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<PerformanceModule>
    X("performance-module", "Adds performance checks.");

} // namespace performance

// This anchor is used to force the linker to link in the generated object file
// and thus register the PerformanceModule.
volatile int PerformanceModuleAnchorSource = 0;

} // namespace clang::tidy
