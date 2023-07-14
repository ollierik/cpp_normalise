#pragma once

#ifndef CPP_NORMALISE_MACRO_GUARD
#define CPP_NORMALISE_MACRO_GUARD


/********************************************
** Platform selection
********************************************/

#if defined(DEBUG) || defined(_DEBUG)
#   define CPP_DEBUG 1
#endif

#if defined(__APPLE__)
#   ifndef CPP_MACOS
#       define CPP_MACOS 1
#   endif
#elif defined(_MSC_VER)
#   ifndef CPP_WIN32
#       define CPP_WIN32 1
#   endif
#endif

/********************************************
 ** Common
 ********************************************/

#ifndef IGNORE_UNUSED
#   define IGNORE_UNUSED(expr)  do { (void)(((expr))); } while (0);
#endif

/********************************************
 ** macOS
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

#define WIN32_LEAN_AND_MEAN
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
