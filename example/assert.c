#include <stdio.h>

#include <god/base/assert.h>
#include <god/base/type.h>

god_int32_t main(god_int32_t argc, char *argv[]) {
    god_assert(1 > 0);
    god_verify(1 > 0);
    god_notreach();
    return 0;
}

