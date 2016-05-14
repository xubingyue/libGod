#pragma once

#include <stddef.h> // offsetof(type, member-desginator) 获得字段在结构体中的偏移量

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef _WIN32
#   define _GOD_WINDOWS_
#else
#   define _GOD_POSIX_
#endif

#ifdef __CYGWIN__
#   define _GOD_WINDOWS_
#   define _GOD_CYGWIN_
#endif

#if defined(linux) || defined(__linux__)
#   define _GOD_LINUX_
#endif

#ifdef __APPLE__
#   define _GOD_OSX_
#   ifndef _GOD_BSD_
#       define _GOD_BSD_
#   endif
#endif

#ifdef __FreeBSD__
#   define _GOD_FREEBSD_
#   define _GOD_BSD_
#endif

#ifdef _GOD_WINDOWS_
#define _GOD_NATIVE_(windows, posix) windows
#else
#define _GOD_NATIVE_(windows, posix) posix
#endif

#ifdef _MSC_VER
#   define _GOD_MSVC_
#   ifdef _M_X64
#       define _GOD_AMD64_
#       define _GOD_IS_64_BITS_
#   elif defined(_M_IX86)
#       define _GOD_I386_
#       define _GOD_IS_32_BITS_
#   endif
#endif

#ifdef __GNUC__
#   define _GOD_GCC_
#   ifdef __x86_64
#       define _GOD_AMD64_
#       define _GOD_IS_64_BITS_
#   elif defined(__i386__)
#       define _GOD_I386_
#       define _GOD_IS_32_BITS_
#   elif defined(__arm64__)
#       define _GOD_ARM64_
#       define _GOD_IS_64_BITS_
#   elif defined(__arm__)
#       define _GOD_ARM_
#       define _GOD_IS_32_BITS_
#   elif defined(__ppc64__)
#       define _GOD_PPC64_
#       define _GOD_IS_64_BITS_
#   elif defined(__ppc__)
#       define _GOD_PPC_
#       define _GOD_IS_32_BITS_
#   endif
#endif

#ifdef __clang__
#   define _GOD_CLANG_
// TODO:
#endif

#ifdef NDEBUG
#   define _GOD_NDEBUG_
#endif

#ifdef _GOD_MSVC_
#   ifndef _DEBUG
#       ifndef _GOD_NDEBUG_
#           define _GOD_NDEBUG_
#       endif
#   endif
#endif

#ifdef _GOD_LINUX_
#   include <sys/sysmacros.h>
#   ifdef major
#       undef major
#   endif
#   ifdef minor
#       undef minor
#   endif
#endif

#define _GOD_INLINE_ inline

#define _GOD_FILE_ __FILE__
#define _GOD_LINE_ __LINE__
#define _GOD_FUNC_ __func__
#define _GOD_DATE_ __DATE__
#define _GOD_TIME_ __TIME__

#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 303)
#   define god_likely(x)   __builtin_expect((x), 1)
#   define god_unlikely(x) __builtin_expect((x), 0)
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
#   define god_likely(x)   (x)
#   define god_unlikely(x) (x)
#else /* not gcc >= 3.3 and not Sun Studio >= 8 */
#   define god_likely(x)   (x)
#   define god_unlikely(x) (x)
#endif

#define _GOD_STRING_(val) #val
#define _GOD_JOIN_(X, Y) X##Y

#define god_offsetof(__type, __member) offsetof(__type, __member)

#ifdef	__cplusplus
}
#endif
