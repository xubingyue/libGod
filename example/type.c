#include <stdio.h>

#include <god/base/type.h>

#define _PRINT_TYPE_(type) printf(#type ": %" PRIuPTR "\n", sizeof(type))

god_int32_t main(god_int32_t argc, char *argv[]) {
    //_PRINT_TYPE_(god_char_ptr);
    //_PRINT_TYPE_(god_const_char_ptr);
    _PRINT_TYPE_(god_float32_t);
    _PRINT_TYPE_(god_float64_t);
    //_PRINT_TYPE_(god_float96_t);
    _PRINT_TYPE_(god_floatmax_t);
    _PRINT_TYPE_(god_size_t);
    _PRINT_TYPE_(god_ssize_t);
    _PRINT_TYPE_(god_ptrdiff_t);
    _PRINT_TYPE_(god_off_t);
    _PRINT_TYPE_(god_time_t);
    _PRINT_TYPE_(god_line_t);
    _PRINT_TYPE_(god_byte_t);
    _PRINT_TYPE_(god_iov_len_t);
    _PRINT_TYPE_(god_file_t);
    _PRINT_TYPE_(god_socket_t);
    _PRINT_TYPE_(god_pid_t);
    _PRINT_TYPE_(god_tid_t);
    _PRINT_TYPE_(god_error_t);
    return 0;
}

