#pragma once

#include <god/base/predef.h>

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#ifdef _GOD_WINDOWS_
#include <windows.h>
#else
#include <errno.h>
#endif

#include <god/base/chartype.h>
#include <god/base/floattype.h>
#include <god/base/inttype.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
#   if	__cplusplus < 201103L
#       define nil NULL
#   else
#       define nil nullptr
#   endif
#else
#   define nil NULL
#endif

typedef size_t god_size_t;
#ifdef _GOD_WINDOWS_
#   ifdef _GOD_IS_64_BITS_
        typedef long god_ssize_t;
#   elif defined(_GOD_IS_32_BITS_)
        typedef int god_ssize_t;
#   endif
#else
typedef ssize_t god_ssize_t;
#endif
typedef ptrdiff_t god_ptrdiff_t;
typedef off_t god_off_t;
typedef time_t god_time_t;

typedef uint32_t god_line_t;
typedef uint8_t god_byte_t;
typedef size_t god_iov_len_t;
typedef int32_t god_file_t;
#define god_invalid_file ((god_file_t)-1)

typedef god_file_t god_socket_t;
#define god_invalid_socket god_invalid_file

#ifdef _GOD_WINDOWS_
    typedef uint32_t god_pid_t;
    typedef uint32_t god_tid_t;
    typedef god_uintptr_t god_fid_t;
#else
    typedef pid_t god_pid_t; // Process ID
    typedef pid_t god_tid_t; // Thread ID
    typedef god_uintptr_t god_fid_t; // Fiber ID
#endif

//typedef size_t god_fls_key_t;

#ifdef _GOD_WINDOWS_
    typedef DWORD god_error_t;
#else
    typedef int32_t god_error_t;
#endif

#ifdef	__cplusplus
}
#endif
