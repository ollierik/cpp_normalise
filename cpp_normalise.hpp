#pragma once

#ifndef CPP_NORMALISE_MACRO_GUARD
#define CPP_NORMALISE_MACRO_GUARD


/********************************************
 * Platform
 ********************************************/

#if defined(DEBUG) || defined(_DEBUG)
#   define CPP_DEBUG 1
#endif

// platform definition
#if defined(__APPLE__)
#   ifndef CPP_MACOS
#       define CPP_MACOS 1
#   endif
#elif defined(_MSC_VER)
#   ifndef CPP_WIN32
#       define CPP_WIN32 1
#   endif
#endif

// architecture definition
#if (defined(__x86_64__) || defined(_M_X64) || defined(i386) || defined(_M_IX86))
#   ifndef CPP_INTEL
#       define CPP_INTEL 1
#   endif
#elif defined(__aarch64__)
#   ifndef CPP_ARM
#       define CPP_ARM 1
#   endif
#endif

// language version definitions
#if (__cplusplus >= 201703L)
#   ifndef CPP_STD17
#       define CPP_STD17 1
#   endif
#endif
#if (__cplusplus >= 201402L)
#   ifndef CPP_STD14
#       define CPP_STD14 1
#   endif
#endif
#if (__cplusplus >= 201103L)
#   ifndef CPP_STD11
#       define CPP_STD11 1
#   endif
#endif
#if (__cplusplus >= 199711L)
#   ifndef CPP_STD98
#       define CPP_STD98 1
#   endif
#endif

/********************************************
 * Common
 ********************************************/

#ifndef IGNORE_UNUSED
#   define IGNORE_UNUSED(expr)  do { (void)(((expr))); } while (0);
#endif // MAYBE_UNUSED

#ifndef MAYBE_UNUSED
#   if CPP_STD17
#       define MAYBE_UNUSED [[maybe_unused]]
#   else
#       if CPP_MACOS
#           define MAYBE_UNUSED __attribute__((unused))
#       else
#           define MAYBE_UNUSED // no WIN32 counterpart
#       endif
#   endif
#endif // MAYBE_UNUSED

/********************************************
 * macOS
 ********************************************/
#if CPP_MACOS

#ifndef RESTRICT
#   define RESTRICT __restrict__
#endif // RESTRICT

#ifndef NEVER_INLINE
#   define NEVER_INLINE __attribute__((noinline))
#endif // NEVER_INLINE

#ifndef FORCE_INLINE
#   define FORCE_INLINE __attribute__((always_inline))
#endif // FORCE_INLINE

#ifndef CPP_PRETTY_FUNCTION
#   define CPP_PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif // CPP_PRETTY_FUNCTION

#endif // CPP_MACOS

/********************************************
 ** macOS Debug
 ********************************************/
#if CPP_MACOS && CPP_DEBUG

#include <cstdio> // printf

#ifndef breakpoint
#   define breakpoint __builtin_trap();
#endif // breakpoint

#ifndef debug_print
#   define debug_print(msg, ...)                                                                \
    do {                                                                                        \
        printf(msg, ##__VA_ARGS__);                                                             \
    } while(0);
#endif // debug_print

#endif // CPP_MACOS && CPP_DEBUG


/********************************************
** Win32
********************************************/
#if CPP_WIN32

#define NOMINMAX // get rid of min and max macros on MSVC
#define WIN32_LEAN_AND_MEAN // don't include stuff that isn't typically needed

#ifndef RESTRICT
#   define RESTRICT __restrict
#endif // RESTRICT

#ifndef NEVER_INLINE
#   define NEVER_INLINE __declspec(noinline)
#endif // NEVER_INLINE

#ifndef FORCE_INLINE
#   define FORCE_INLINE __forceinline
#endif // FORCE_INLINE

#ifndef CPP_PRETTY_FUNCTION
#   define CPP_PRETTY_FUNCTION __FUNCSIG__
#endif // CPP_PRETTY_FUNCTION

#endif // CPP_WIN32

/********************************************
** Win32 Debug
********************************************/
#if CPP_WIN32 && CPP_DEBUG

#include <Windows.h>    // OutputDebugStringA
#include <intrin.h>     // __debugbreak() 
#include <chrono>       // debug_print time functions

#ifndef breakpoint
#   define breakpoint __debugbreak()
#endif // breakpoint

#ifndef debug_print
#   define debug_print(msg, ...)                                                                \
    do {                                                                                        \
        char buf[256];                                                                          \
        snprintf_s(buf, 256, msg, __VA_ARGS__);                                                 \
        OutputDebugStringA(buf);                                                                \
    } while(0);
#endif // debug_print

#endif // CPP_WIN32 && CPP_DEBUG

/********************************************
** Debug helpers
********************************************/

#if CPP_DEBUG

#ifndef debug_line
#   define debug_line(msg, ...)                                                                 \
    do {                                                                                        \
        const auto epoch = std::chrono::system_clock::now().time_since_epoch();                 \
        const auto timeunits = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);    \
        const long unsigned int timeu = timeunits.count();                                      \
        debug_print("%lu: ", timeu);                                                            \
        debug_print(msg "\n", __VA_ARGS__);                                                     \
    } while(0);
#endif // debug_line

#ifndef errorif
#   define errorif(condition, msg, ...)                                                         \
    do {                                                                                        \
        if (((condition))) {                                                                    \
            debug_print(msg "\n", ##__VA_ARGS__);                                               \
            breakpoint;                                                                         \
        }                                                                                       \
    } while (0);
#endif // errorif

#endif // CPP_DEBUG

/********************************************
 ** Release and fallback
 *******************************************/

#ifndef RESTRICT
#   define RESTRICT
#endif // RESTRICT

#ifndef NEVER_INLINE
#   define NEVER_INLINE
#endif // NEVER_INLINE

#ifndef FORCE_INLINE
#   define FORCE_INLINE
#endif // FORCE_INLINE

#ifndef breakpoint
#   define breakpoint ((void)0);
#endif // breakpoint

#ifndef debug_print
#   define debug_print(msg, ...) ((void)0)
#endif // debug_print

#ifndef debug_line
#   define debug_line(msg, ...) ((void)0)
#endif // debug_print

#ifndef errorif
#   define errorif(condition, msg, ...) ((void)0)
#endif // errorif


#endif // CPP_NORMALISE_MACRO_GUARD
