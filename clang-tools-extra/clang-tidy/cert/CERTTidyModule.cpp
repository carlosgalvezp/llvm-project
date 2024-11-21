//===--- CERTTidyModule.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../bugprone/BadSignalToKillThreadCheck.h"
#include "../bugprone/PointerArithmeticOnPolymorphicObjectCheck.h"
#include "../bugprone/ReservedIdentifierCheck.h"
#include "../bugprone/SignalHandlerCheck.h"
#include "../bugprone/SignedCharMisuseCheck.h"
#include "../bugprone/SizeofExpressionCheck.h"
#include "../bugprone/SpuriouslyWakeUpFunctionsCheck.h"
#include "../bugprone/SuspiciousMemoryComparisonCheck.h"
#include "../bugprone/UnhandledSelfAssignmentCheck.h"
#include "../bugprone/UnsafeFunctionsCheck.h"
#include "../bugprone/UnusedReturnValueCheck.h"
#include "../concurrency/ThreadCanceltypeAsynchronousCheck.h"
#include "../google/UnnamedNamespaceInHeaderCheck.h"
#include "../misc/NewDeleteOverloadsCheck.h"
#include "../misc/NonCopyableObjects.h"
#include "../misc/StaticAssertCheck.h"
#include "../misc/ThrowByValueCatchByReferenceCheck.h"
#include "../performance/MoveConstructorInitCheck.h"
#include "../readability/EnumInitialValueCheck.h"
#include "../readability/UppercaseLiteralSuffixCheck.h"
#include "CommandProcessorCheck.h"
#include "DefaultOperatorNewAlignmentCheck.h"
#include "DontModifyStdNamespaceCheck.h"
#include "FloatLoopCounter.h"
#include "LimitedRandomnessCheck.h"
#include "MutatingCopyCheck.h"
#include "NonTrivialTypesLibcMemoryCallsCheck.h"
#include "ProperlySeededRandomGeneratorCheck.h"
#include "SetLongJmpCheck.h"
#include "StaticObjectExceptionCheck.h"
#include "StrToNumCheck.h"
#include "ThrownExceptionTypeCheck.h"
#include "VariadicFunctionDefCheck.h"

namespace {

// Checked functions for cert-err33-c.
// The following functions are deliberately excluded because they can be called
// with NULL argument and in this case the check is not applicable:
// `mblen, mbrlen, mbrtowc, mbtowc, wctomb, wctomb_s`.
// FIXME: The check can be improved to handle such cases.
const llvm::StringRef CertErr33CCheckedFunctions = "^::aligned_alloc;"
                                                   "^::asctime_s;"
                                                   "^::at_quick_exit;"
                                                   "^::atexit;"
                                                   "^::bsearch;"
                                                   "^::bsearch_s;"
                                                   "^::btowc;"
                                                   "^::c16rtomb;"
                                                   "^::c32rtomb;"
                                                   "^::calloc;"
                                                   "^::clock;"
                                                   "^::cnd_broadcast;"
                                                   "^::cnd_init;"
                                                   "^::cnd_signal;"
                                                   "^::cnd_timedwait;"
                                                   "^::cnd_wait;"
                                                   "^::ctime_s;"
                                                   "^::fclose;"
                                                   "^::fflush;"
                                                   "^::fgetc;"
                                                   "^::fgetpos;"
                                                   "^::fgets;"
                                                   "^::fgetwc;"
                                                   "^::fopen;"
                                                   "^::fopen_s;"
                                                   "^::fprintf;"
                                                   "^::fprintf_s;"
                                                   "^::fputc;"
                                                   "^::fputs;"
                                                   "^::fputwc;"
                                                   "^::fputws;"
                                                   "^::fread;"
                                                   "^::freopen;"
                                                   "^::freopen_s;"
                                                   "^::fscanf;"
                                                   "^::fscanf_s;"
                                                   "^::fseek;"
                                                   "^::fsetpos;"
                                                   "^::ftell;"
                                                   "^::fwprintf;"
                                                   "^::fwprintf_s;"
                                                   "^::fwrite;"
                                                   "^::fwscanf;"
                                                   "^::fwscanf_s;"
                                                   "^::getc;"
                                                   "^::getchar;"
                                                   "^::getenv;"
                                                   "^::getenv_s;"
                                                   "^::gets_s;"
                                                   "^::getwc;"
                                                   "^::getwchar;"
                                                   "^::gmtime;"
                                                   "^::gmtime_s;"
                                                   "^::localtime;"
                                                   "^::localtime_s;"
                                                   "^::malloc;"
                                                   "^::mbrtoc16;"
                                                   "^::mbrtoc32;"
                                                   "^::mbsrtowcs;"
                                                   "^::mbsrtowcs_s;"
                                                   "^::mbstowcs;"
                                                   "^::mbstowcs_s;"
                                                   "^::memchr;"
                                                   "^::mktime;"
                                                   "^::mtx_init;"
                                                   "^::mtx_lock;"
                                                   "^::mtx_timedlock;"
                                                   "^::mtx_trylock;"
                                                   "^::mtx_unlock;"
                                                   "^::printf_s;"
                                                   "^::putc;"
                                                   "^::putwc;"
                                                   "^::raise;"
                                                   "^::realloc;"
                                                   "^::remove;"
                                                   "^::rename;"
                                                   "^::scanf;"
                                                   "^::scanf_s;"
                                                   "^::setlocale;"
                                                   "^::setvbuf;"
                                                   "^::signal;"
                                                   "^::snprintf;"
                                                   "^::snprintf_s;"
                                                   "^::sprintf;"
                                                   "^::sprintf_s;"
                                                   "^::sscanf;"
                                                   "^::sscanf_s;"
                                                   "^::strchr;"
                                                   "^::strerror_s;"
                                                   "^::strftime;"
                                                   "^::strpbrk;"
                                                   "^::strrchr;"
                                                   "^::strstr;"
                                                   "^::strtod;"
                                                   "^::strtof;"
                                                   "^::strtoimax;"
                                                   "^::strtok;"
                                                   "^::strtok_s;"
                                                   "^::strtol;"
                                                   "^::strtold;"
                                                   "^::strtoll;"
                                                   "^::strtoul;"
                                                   "^::strtoull;"
                                                   "^::strtoumax;"
                                                   "^::strxfrm;"
                                                   "^::swprintf;"
                                                   "^::swprintf_s;"
                                                   "^::swscanf;"
                                                   "^::swscanf_s;"
                                                   "^::thrd_create;"
                                                   "^::thrd_detach;"
                                                   "^::thrd_join;"
                                                   "^::thrd_sleep;"
                                                   "^::time;"
                                                   "^::timespec_get;"
                                                   "^::tmpfile;"
                                                   "^::tmpfile_s;"
                                                   "^::tmpnam;"
                                                   "^::tmpnam_s;"
                                                   "^::tss_create;"
                                                   "^::tss_get;"
                                                   "^::tss_set;"
                                                   "^::ungetc;"
                                                   "^::ungetwc;"
                                                   "^::vfprintf;"
                                                   "^::vfprintf_s;"
                                                   "^::vfscanf;"
                                                   "^::vfscanf_s;"
                                                   "^::vfwprintf;"
                                                   "^::vfwprintf_s;"
                                                   "^::vfwscanf;"
                                                   "^::vfwscanf_s;"
                                                   "^::vprintf_s;"
                                                   "^::vscanf;"
                                                   "^::vscanf_s;"
                                                   "^::vsnprintf;"
                                                   "^::vsnprintf_s;"
                                                   "^::vsprintf;"
                                                   "^::vsprintf_s;"
                                                   "^::vsscanf;"
                                                   "^::vsscanf_s;"
                                                   "^::vswprintf;"
                                                   "^::vswprintf_s;"
                                                   "^::vswscanf;"
                                                   "^::vswscanf_s;"
                                                   "^::vwprintf_s;"
                                                   "^::vwscanf;"
                                                   "^::vwscanf_s;"
                                                   "^::wcrtomb;"
                                                   "^::wcschr;"
                                                   "^::wcsftime;"
                                                   "^::wcspbrk;"
                                                   "^::wcsrchr;"
                                                   "^::wcsrtombs;"
                                                   "^::wcsrtombs_s;"
                                                   "^::wcsstr;"
                                                   "^::wcstod;"
                                                   "^::wcstof;"
                                                   "^::wcstoimax;"
                                                   "^::wcstok;"
                                                   "^::wcstok_s;"
                                                   "^::wcstol;"
                                                   "^::wcstold;"
                                                   "^::wcstoll;"
                                                   "^::wcstombs;"
                                                   "^::wcstombs_s;"
                                                   "^::wcstoul;"
                                                   "^::wcstoull;"
                                                   "^::wcstoumax;"
                                                   "^::wcsxfrm;"
                                                   "^::wctob;"
                                                   "^::wctrans;"
                                                   "^::wctype;"
                                                   "^::wmemchr;"
                                                   "^::wprintf_s;"
                                                   "^::wscanf;"
                                                   "^::wscanf_s;";

} // namespace

namespace clang::tidy {
namespace cert {

class CERTModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    // C++ checkers
    // CON
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SpuriouslyWakeUpFunctionsCheck, 
        "cert-con54-cpp");
    // CTR
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::PointerArithmeticOnPolymorphicObjectCheck,
            "cert-ctr56-cpp");
    // DCL
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, VariadicFunctionDefCheck, "cert-dcl50-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::ReservedIdentifierCheck, 
        "cert-dcl51-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::NewDeleteOverloadsCheck, 
        "cert-dcl54-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DontModifyStdNamespaceCheck, 
        "cert-dcl58-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, google::build::UnnamedNamespaceInHeaderCheck, 
        "cert-dcl59-cpp");
    // ERR
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::ThrowByValueCatchByReferenceCheck, 
        "cert-err09-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, SetLongJmpCheck, "cert-err52-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StaticObjectExceptionCheck, "cert-err58-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ThrownExceptionTypeCheck, "cert-err60-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::ThrowByValueCatchByReferenceCheck, 
        "cert-err61-cpp");
    // MEM
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, DefaultOperatorNewAlignmentCheck, 
        "cert-mem57-cpp");
    // MSC
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, LimitedRandomnessCheck, "cert-msc50-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProperlySeededRandomGeneratorCheck, 
        "cert-msc51-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SignalHandlerCheck, 
        "cert-msc54-cpp");
    // OOP
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, performance::MoveConstructorInitCheck, 
        "cert-oop11-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UnhandledSelfAssignmentCheck, 
        "cert-oop54-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, NonTrivialTypesLibcMemoryCallsCheck, 
        "cert-oop57-cpp");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, MutatingCopyCheck, 
        "cert-oop58-cpp");

    // C checkers
    // ARR
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SizeofExpressionCheck, 
        "cert-arr39-c");
    // CON
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SpuriouslyWakeUpFunctionsCheck, 
        "cert-con36-c");
    // DCL
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::StaticAssertCheck, "cert-dcl03-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::UppercaseLiteralSuffixCheck, 
        "cert-dcl16-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::ReservedIdentifierCheck, 
        "cert-dcl37-c");
    // ENV
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, CommandProcessorCheck, "cert-env33-c");
    // ERR
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UnusedReturnValueCheck, 
        "cert-err33-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, StrToNumCheck, "cert-err34-c");
    // EXP
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SuspiciousMemoryComparisonCheck, 
        "cert-exp42-c");
    // FLP
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, FloatLoopCounter, "cert-flp30-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SuspiciousMemoryComparisonCheck, 
        "cert-flp37-c");
    // FIO
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, misc::NonCopyableObjectsCheck, "cert-fio38-c");
    // INT
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, readability::EnumInitialValueCheck, 
        "cert-int09-c");
    // MSC
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UnsafeFunctionsCheck, 
        "cert-msc24-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, LimitedRandomnessCheck, "cert-msc30-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, ProperlySeededRandomGeneratorCheck, 
        "cert-msc32-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::UnsafeFunctionsCheck, 
        "cert-msc33-c");
    // POS
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::BadSignalToKillThreadCheck, 
        "cert-pos44-c");
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, concurrency::ThreadCanceltypeAsynchronousCheck,
            "cert-pos47-c");
    // SIG
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SignalHandlerCheck, "cert-sig30-c");
    // STR
    CLANG_TIDY_REGISTER_CHECK(CheckFactories, bugprone::SignedCharMisuseCheck, 
        "cert-str34-c");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    ClangTidyOptions::OptionMap &Opts = Options.CheckOptions;
    Opts["cert-arr39-c.WarnOnSizeOfConstant"] = "false";
    Opts["cert-arr39-c.WarnOnSizeOfIntegerExpression"] = "false";
    Opts["cert-arr39-c.WarnOnSizeOfThis"] = "false";
    Opts["cert-arr39-c.WarnOnSizeOfCompareToConstant"] = "false";
    Opts["cert-arr39-c.WarnOnSizeOfPointer"] = "false";
    Opts["cert-arr39-c.WarnOnSizeOfPointerToAggregate"] = "false";
    Opts["cert-dcl16-c.NewSuffixes"] = "L;LL;LU;LLU";
    Opts["cert-err33-c.CheckedFunctions"] = CertErr33CCheckedFunctions;
    Opts["cert-err33-c.AllowCastToVoid"] = "true";
    Opts["cert-oop54-cpp.WarnOnlyIfThisHasSuspiciousField"] = "false";
    Opts["cert-str34-c.DiagnoseSignedUnsignedCharComparisons"] = "false";
    return Options;
  }
};

} // namespace cert

// Register the MiscTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<cert::CERTModule>
    X("cert-module",
      "Adds lint checks corresponding to CERT secure coding guidelines.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the CERTModule.
volatile int CERTModuleAnchorSource = 0;

} // namespace clang::tidy
