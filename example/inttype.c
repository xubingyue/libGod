#include <stdio.h>

#include <god/base/inttype.h>

#define _PRINT_TYPE_(type) printf(#type ": %" PRIuPTR "\n", sizeof(type))

god_int32_t main(god_int32_t argc, char *argv[]) {
    _PRINT_TYPE_(god_int8_t);
    _PRINT_TYPE_(god_int16_t);
    _PRINT_TYPE_(god_int32_t);
    _PRINT_TYPE_(god_int64_t);
    printf("\n");

    _PRINT_TYPE_(god_uint8_t);
    _PRINT_TYPE_(god_uint16_t);
    _PRINT_TYPE_(god_uint32_t);
    _PRINT_TYPE_(god_uint64_t);
    printf("\n");

    _PRINT_TYPE_(god_int_least8_t);
    _PRINT_TYPE_(god_int_least16_t);
    _PRINT_TYPE_(god_int_least32_t);
    _PRINT_TYPE_(god_int_least64_t);
    printf("\n");

    _PRINT_TYPE_(god_uint_least8_t);
    _PRINT_TYPE_(god_uint_least16_t);
    _PRINT_TYPE_(god_uint_least32_t);
    _PRINT_TYPE_(god_uint_least64_t);
    printf("\n");

    _PRINT_TYPE_(god_int_fast8_t);
    _PRINT_TYPE_(god_int_fast16_t);
    _PRINT_TYPE_(god_int_fast32_t);
    _PRINT_TYPE_(god_int_fast64_t);
    printf("\n");

    _PRINT_TYPE_(god_uint_fast8_t);
    _PRINT_TYPE_(god_uint_fast16_t);
    _PRINT_TYPE_(god_uint_fast32_t);
    _PRINT_TYPE_(god_uint_fast64_t);
    printf("\n");

    _PRINT_TYPE_(god_intptr_t);
    _PRINT_TYPE_(god_uintptr_t);
    printf("\n");

    _PRINT_TYPE_(god_intmax_t);
    _PRINT_TYPE_(god_uintmax_t);
    printf("\n");

    return 0;
}

