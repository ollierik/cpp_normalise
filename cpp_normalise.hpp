#pragma once

#ifndef CPP_NORMALISE_MACRO_GUARD
#define CPP_NORMALISE_MACRO_GUARD


/********************************************
** Common
********************************************/

#ifndef IGNORE_UNUSED
    #define IGNORE_UNUSED(expr)  do { (void)(expr); } while (0)
#endif

#ifndef SNPRINTF
    #define SNPRINTF(buffer, size, format, ...) snprintf(buffer, size, format, __VA_ARGS__)
#endif


/********************************************
** Apple Xcode
********************************************/
#if defined(__APPLE_CPP__)

#ifndef NEVER_INLINE
    #define NEVER_INLINE __attribute__((noinline))
#endif // NEVER_INLINE

#ifndef RESTRICT
    #define RESTRICT __restrict__
#endif // RESTRICT

#ifndef FORCE_INLINE
    #define FORCE_INLINE __attribute__((always_inline))
#endif // FORCE_INLINE

/********************************************
 ***** Apple Xcode - Debug
********************************************/
#if defined(DEBUG) || defined(_DEBUG)

#ifndef breakpoint
    #define breakpoint __builtin_trap();
#endif // breakpoint

#ifndef debug_print
    #define debug_print(msg, ...)                                                               \
    do {                                                                                        \
        printf(msg, ...);                                                                       \
    } while(0);
#endif // debug_print

#ifndef debug_println
    #define debug_println(msg, ...)                                                             \
    do {                                                                                        \
        char buf[256];                                                                          \
        const auto epoch = std::chrono::system_clock::now().time_since_epoch();                 \
        const auto timeunits = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);    \
        const long unsigned int timeu = timeunits.count();                                      \
        SNPRINTF(buf, 256, "%lu: ", timeu);                                                     \
        printf("%s", buf);                                                                      \
        sprintf(buf, msg, ##__VA_ARGS__);                                                       \
        printf("%s\n", buf);                                                                    \
    } while(0);
#endif // debug_println

#ifndef errorif
    #define errorif(condition, msg, ...)                                                        \
    do {                                                                                        \
        if ((condition)) {                                                                      \
            debug_print(msg "\n", ##__VA_ARGS__); breakpoint;                                   \
        }                                                                                       \
    } while (0);
#endif // errorif

#endif // if DEBUG

#endif // if Apple


/********************************************
 ** Windows MSVC
 *******************************************/
#if defined (_MSC_VER)

#ifndef IS_MSVC
	#define IS_MSVC 1
#endif

#define NOMINMAX // get rid of min and max macros on MSVC

#ifndef RESTRICT
    #define RESTRICT __restrict
#endif

#ifndef FORCE_INLINE
    #define FORCE_INLINE __forceinline
#endif // FORCE_INLINE

#ifndef NEVER_INLINE
    #define NEVER_INLINE __declspec(noinline)
#endif // NEVER_INLINE

/********************************************
 **** Windows MSVC - Debug
 *******************************************/
#if defined(DEBUG) || defined(_DEBUG)

#include <Windows.h>    // OutputDebugStringA
#include <intrin.h>     // __debugbreak() 
#include <chrono>       // debug_print time functions

#ifndef breakpoint
    #define breakpoint __debugbreak()
#endif // breakpoint

#ifndef debug_print
    #define debug_print(msg, ...)                                                               \
    do {                                                                                        \
        char buf[256];                                                                          \
        SNPRINTF(buf, 256, msg, __VA_ARGS__);                                                   \
        OutputDebugStringA(buf);                                                                \
    } while(0);
#endif // debug_print

#ifndef debug_println
    #define debug_println(msg, ...)                                                             \
    do {                                                                                        \
        char buf[256];                                                                          \
        const auto epoch = std::chrono::system_clock::now().time_since_epoch();                 \
        const auto timeunits = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);    \
        const long unsigned int timeu = timeunits.count();                                      \
        SNPRINTF(buf, 256, "%lu: ", timeu);                                                     \
        OutputDebugStringA(buf);                                                                \
        SNPRINTF(buf, 256, msg, __VA_ARGS__);                                                   \
        OutputDebugStringA(buf);                                                                \
        OutputDebugStringA("\n");                                                               \
    } while(0);
#endif // debug_print

#ifndef errorif
    #define errorif(condition, msg, ...)                                                        \
    do {                                                                                        \
        if ((condition)) {                                                                      \
            debug_print(msg "\n", __VA_ARGS__); breakpoint;                                     \
        }                                                                                       \
    } while (0);
#endif // errorif

#endif // if DEBUG

#endif // if Windows


/********************************************
 ** TODO: GNU Linux
 *******************************************/
#if defined(__GNUC__)
    // TODO
#endif // GNU

/********************************************
 ** Release and as fallback
 *******************************************/

#ifndef RESTRICT
    #define RESTRICT
#endif // RESTRICT

#ifndef FORCE_INLINE
    #define FORCE_INLINE
#endif // FORCE_INLINE

#ifndef breakpoint
    #define breakpoint ((void)0);
#endif // breakpoint

#ifndef debug_println
    #define debug_println(msg, ...) ((void)0)
#endif // debug_print

#ifndef debug_print
    #define debug_print(msg, ...) ((void)0)
#endif // debug_print

#ifndef errorif
    #define errorif(condition, msg, ...) ((void)0)
#endif // errorif



#endif // CPP_NORMALISE_MACRO_GUARD



