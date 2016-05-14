#include <stdio.h>

#include <god/base/error.h>
#include <god/base/predef.h>
#include <god/base/type.h>
#include <god/fiber/fiber.h>

void func1(god_intptr_t param) {
    god_size_t count = 10000000 * 1;
    god_size_t i;
    for (i = 0; i < count; ++i) {
        god_error_t err = god_fiber_yield();
        if (god_unlikely(err != EOK)) {
            printf("god_fiber_yield error\n");
        }
    }
}

god_int32_t main(god_int32_t argc, char *argv[]) {
    god_size_t count = 10;
    god_error_t err = god_fiber_scheduler_init();
    if (err != EOK) {
        printf("god_fiber_scheduler_init: %d\n", err);
        return -1;
    }
    god_size_t i;
    for (i = 0; i < count; ++i) {
        err = god_fiber_create(nil, func1, 0);
        if (err != EOK) {
            printf("god_fiber_create: %d\n", err);
            return -1;
        }
    }
    err = god_fiber_scheduler_dispatch();
    if (err != EOK) {
        printf("god_fiber_scheduler_dispatch: %d\n", err);
        return -1;
    }
    err = god_fiber_scheduler_destroy();
    if (err != EOK) {
        printf("god_fiber_scheduler_destroy: %d\n", err);
        return -1;
    }
    return 0;
}
