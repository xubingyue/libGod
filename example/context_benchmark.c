#include <stdlib.h>

#include <god/context/context.h>

static const god_size_t k_stacksize = 1024 * 64;

god_context_t g_main_fiber = god_invalid_context;
god_context_t g_child_fiber = god_invalid_context;

void child_entry(god_intptr_t argv) {
    while (true) {
        god_swap_context(&g_child_fiber, g_main_fiber, (god_intptr_t)0, false);
    }
}

god_int32_t main(god_int32_t argc, char *argv[]) {
    god_uint64_t count = 10000;
    if (argc > 1) {
        count = strtoul(argv[1], 0, 10);
    }
    void *p = malloc(k_stacksize);
    void *sp = (char *)p + k_stacksize;
    g_child_fiber = god_make_context(sp, k_stacksize, child_entry);

    god_uint64_t i;
    for (i = 0; i < count; ++i) {
        god_swap_context(&g_main_fiber, g_child_fiber, (god_intptr_t)0, false);
    }
    free(p);
    return 0;
}
