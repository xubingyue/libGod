#include <stdio.h>

#include <god/base/predef.h>
#include <god/base/type.h>

god_int32_t main(god_int32_t argc, char *argv[]) {
#ifdef _GOD_WINDOWS_
    printf("_GOD_WINDOWS_\n");
#endif
#ifdef _GOD_POSIX_
    printf("_GOD_POSIX_\n");
#endif
#ifdef _GOD_LINUX_
    printf("_GOD_LINUX_\n");
#endif
#ifdef _GOD_CYGWIN_
    printf("_GOD_CYGWIN_\n");
#endif
#ifdef _GOD_OSX_
    printf("_GOD_OSX_\n");
#endif
#ifdef _GOD_BSD_
    printf("_GOD_BSD_\n");
#endif
#ifdef _GOD_FREEBSD_
    printf("_GOD_FREEBSD_\n");
#endif
#ifdef _GOD_MSVC_
    printf("_GOD_MSVC_\n");
#endif
#ifdef _GOD_GCC_
    printf("_GOD_GCC_\n");
#endif
#ifdef _GOD_CLANG_
    printf("_GOD_CLANG_\n");
#endif
#ifdef _GOD_IS_64_BITS_
    printf("_GOD_IS_64_BITS_\n");
#endif
#ifdef _GOD_IS_32_BITS_
    printf("_GOD_IS_32_BITS_\n");
#endif
#ifdef _GOD_AMD64_
    printf("_GOD_AMD64_\n");
#endif
#ifdef _GOD_I386_
    printf("_GOD_I386_\n");
#endif
#ifdef _GOD_ARM_
    printf("_GOD_ARM_\n");
#endif
#ifdef _GOD_ARM64_
    printf("_GOD_ARM64_\n");
#endif
#ifdef _GOD_PPC_
    printf("_GOD_PPC_\n");
#endif
#ifdef _GOD_PPC64_
    printf("_GOD_PPC64_\n");
#endif
#ifdef _GOD_NDEBUG_
    printf("_GOD_NDEBUG_\n");
#endif
#ifdef _GOD_INLINE_
    printf("_GOD_INLINE_\n");
#endif
#ifdef _GOD_FILE_
    printf("_GOD_FILE_\n");
#endif
#ifdef _GOD_LINE_
    printf("_GOD_LINE_\n");
#endif
#ifdef _GOD_FUNC_
    printf("_GOD_FUNC_\n");
#endif
#ifdef _GOD_DATE_
    printf("_GOD_DATE_\n");
#endif
#ifdef _GOD_TIME_
    printf("_GOD_TIME_\n");
#endif
    return 0;
}

