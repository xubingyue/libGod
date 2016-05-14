#include <stdio.h>
#include <stdlib.h>

#include <god/context/context.h>

static const god_size_t k_stacksize = 1024 * 64;

god_context_t g_main_fiber = god_invalid_context;
god_context_t g_child_fiber = god_invalid_context;

void child_entry(god_intptr_t argv) {
    god_intptr_t val = argv;
    printf("child: before jump to main, val: %" PRIdPTR "\n", val);
    val *= 10;
    val = god_swap_context(&g_child_fiber, g_main_fiber, val, false);
    printf("child: after jump to main, val: %" PRIdPTR "\n", val);
}

god_int32_t main(god_int32_t argc, char *argv[]) {
    void *p = malloc(k_stacksize);
    void *sp = (char *)p + k_stacksize;
    g_child_fiber = god_make_context(sp, k_stacksize, child_entry);

    god_intptr_t val = 1;
    printf("main: before jump to child, val: %" PRIdPTR "\n", val);
    val = god_swap_context(&g_main_fiber, g_child_fiber, val, false);
    printf("main: after jump to child, val: %" PRIdPTR "\n", val);
    free(p);
    printf("Exit..\n");
    return 0;
}
