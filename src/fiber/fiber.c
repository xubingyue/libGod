#include <god/fiber/fiber.h>

#include <stdlib.h> // malloc

#include <god/base/assert.h>
#include <god/base/predef.h>

#define STABLE_SCHEDULER

#ifdef STABLE_SCHEDULER
#pragma message("Build on stable mode")
#else
#pragma message("Build on fast mode")
#endif

static const size_t k_pagesize = 4096;
static const size_t k_stack_size = 4096 * 64;

typedef enum {
    god_fiber_state_init = 0,
    god_fiber_state_suspended,
    god_fiber_state_running,
    god_fiber_state_stopped,
} god_fiber_state_t;

typedef struct god_fiber {
#ifndef _GOD_NDEBUG_
    god_fiber_scheduler_ptr scheduler;
#endif
    //god_list_node_t all_node;
    god_list_node_t node;
    void *stack_pointer;
    size_t stack_size;
    //fd_t id;
    god_context_t context;
    god_fiber_entry_t entry;
    god_intptr_t param;
    god_fiber_state_t state;
} god_fiber_t;

typedef struct god_fiber_scheduler {
    //god_list_t all_list;
    god_list_t list;
    god_fiber_t root_fiber;
    god_fiber_ptr cur_fiber;
    god_fiber_ptr dispatch_fiber;
} god_fiber_scheduler_t;

static void god_fiber_entry(god_intptr_t val);

inline static god_fiber_ptr new_fiber(god_size_t stack_size, god_fiber_entry_t entry, god_intptr_t param) {
    //stack_size = ceil_align(stack_size, k_pagesize);
    stack_size = ((stack_size + k_pagesize - 1) & (~(k_pagesize - 1)));
    void *p = malloc(stack_size);
    if (god_unlikely(p == nil)) {
        return god_invalid_fiber;
    }
    size_t left_stack_size = stack_size - sizeof(god_fiber_t);
    void *stack_pointer = (god_byte_t *)p + left_stack_size;
    god_fiber_ptr f = (god_fiber_ptr)stack_pointer;
#ifndef _GOD_NDEBUG_
    f->scheduler = god_invalid_fiber_scheduler;
#endif
    //god_list_node_init(&f->all_node);
    god_list_node_init(&f->node);
    f->stack_pointer = stack_pointer;
    f->stack_size = left_stack_size;
    f->context = god_make_context(stack_pointer, left_stack_size, god_fiber_entry);
    f->entry = entry;
    f->param = param;
    f->state = god_fiber_state_init;
    return f;
}

inline static void delete_fiber(god_fiber_ptr f) {
    void *p = (god_byte_t *)f->stack_pointer - f->stack_size;
    free(p);
}

static __thread god_fiber_scheduler_ptr g_scheduler = god_invalid_fiber_scheduler;

/*god_fiber_scheduler_ptr god_fiber_scheduler_self(void) {
    return g_scheduler;
}*/

god_error_t god_fiber_scheduler_init(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler == god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler != god_invalid_fiber_scheduler)) {
        return -1; //TODO：INFIBERSCHED;
    }
    static god_fiber_scheduler_t sched;
    //god_list_init(&sched.all_list);
    god_list_init(&sched.list);
    sched.root_fiber.stack_pointer = nil;
    sched.root_fiber.context = god_invalid_context;
    sched.root_fiber.state = god_fiber_state_running;
    sched.cur_fiber = &sched.root_fiber;
    sched.dispatch_fiber = nil;

    g_scheduler = &sched;
    return EOK;
}

god_error_t god_fiber_scheduler_destroy(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
    g_scheduler = god_invalid_fiber_scheduler;
    return EOK;
}

god_error_t god_fiber_scheduler_dispatch(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
    god_fiber_ptr cur_fiber = cur_scheduler->cur_fiber;

    god_fiber_ptr origin_dispatch_fiber = cur_scheduler->dispatch_fiber;
    cur_scheduler->dispatch_fiber = cur_fiber;

#ifdef STABLE_SCHEDULER
    while (god_likely(!god_list_empty(&cur_scheduler->list))) {
#else
    if (god_likely(!god_list_empty(&cur_scheduler->list))) {
#endif
        {
            god_fiber_ptr next_fiber = god_list_data(god_list_front(&cur_scheduler->list), god_fiber_t, node);
            god_list_pop_front(&cur_scheduler->list);

            cur_fiber->state = god_fiber_state_suspended;
            god_swap_context(&cur_fiber->context, next_fiber->context, (god_intptr_t)next_fiber, false);
#ifdef STABLE_SCHEDULER
            if (next_fiber->state == god_fiber_state_stopped) {
                //god_list_erase(&next_fiber->all_node);
                delete_fiber(next_fiber);
            }
        }
#else
        }
        if (god_unlikely(cur_scheduler->cur_fiber->state == god_fiber_state_stopped)) {
            //god_list_erase(&cur_scheduler->cur_fiber->all_node);
            delete_fiber(cur_scheduler->cur_fiber);
        }
#endif
        cur_fiber->state = god_fiber_state_running;
        cur_scheduler->cur_fiber = cur_fiber;
    }

    cur_scheduler->dispatch_fiber = origin_dispatch_fiber;

    return EOK;
}

god_fid_t god_fiber_id(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return 0;
    }
    return (god_fid_t)(cur_scheduler->cur_fiber);
}

god_fiber_ptr god_fiber_self(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return god_invalid_fiber;
    }
    return cur_scheduler->cur_fiber;
}

static void god_fiber_entry(god_intptr_t val) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    god_fiber_ptr cur_fiber = (god_fiber_ptr)val;
    cur_fiber->state = god_fiber_state_running;
    cur_scheduler->cur_fiber = cur_fiber;

    cur_fiber->entry(cur_fiber->param);

#ifdef STABLE_SCHEDULER
    god_fiber_ptr next_fiber = cur_scheduler->dispatch_fiber;
#else
    god_fiber_ptr next_fiber = god_invalid_fiber;
    if (god_unlikely(god_list_empty(&cur_scheduler->list))) {
        next_fiber = cur_scheduler->dispatch_fiber;
    } else {
        next_fiber = god_list_data(god_list_front(&cur_scheduler->list), god_fiber_t, node);
        god_list_pop_front(&cur_scheduler->list);
    }
#endif

    cur_fiber->state = god_fiber_state_stopped;
    god_swap_context(&cur_fiber->context, next_fiber->context, (god_intptr_t)next_fiber, false);
    god_notreach();
}

god_error_t god_fiber_create(god_fiber_ptr *fiber, god_fiber_entry_t entry, god_intptr_t param) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
    god_fiber_ptr f = new_fiber(k_stack_size, entry, param);
    if (god_unlikely(f == god_invalid_fiber)) {
        return ENOMEM;
    }

#ifndef _GOD_NDEBUG_
    f->scheduler = cur_scheduler;
#endif
    //god_list_push_back(&cur_scheduler->all_list, &f->all_node);
    god_list_push_back(&cur_scheduler->list, &f->node);

    if (god_unlikely(fiber != nil)) {
        *fiber = f;
    }
    return EOK;
}

god_error_t god_fiber_yield(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
    if (god_unlikely(cur_scheduler->dispatch_fiber == nil)) {
        return -1; //TODO：INROOTFIBER;
    }

    god_fiber_ptr cur_fiber = cur_scheduler->cur_fiber;
#ifndef _GOD_NDEBUG_
    assert(cur_fiber->scheduler == cur_scheduler);
#endif
    if (god_unlikely(god_list_empty(&cur_scheduler->list))) {
        return EOK; // 没有其他等待运行的fiber，无需让出CPU。
    }
    god_list_push_back(&cur_scheduler->list, &cur_fiber->node);

    {
#ifdef STABLE_SCHEDULER
        god_fiber_ptr next_fiber = cur_scheduler->dispatch_fiber;
#else
        god_fiber_ptr next_fiber = god_list_data(god_list_front(&cur_scheduler->list), god_fiber_t, node);
        god_list_pop_front(&cur_scheduler->list);
#endif

        cur_fiber->state = god_fiber_state_suspended;
        god_swap_context(&cur_fiber->context, next_fiber->context, (god_intptr_t)next_fiber, false);
    }
#ifndef STABLE_SCHEDULER
    if (god_unlikely(cur_scheduler->cur_fiber->state == god_fiber_state_stopped)) {
        //god_list_erase(&cur_scheduler->cur_fiber->all_node);
        delete_fiber(cur_scheduler->cur_fiber);
    }
#endif
    cur_fiber->state = god_fiber_state_running;
    cur_scheduler->cur_fiber = cur_fiber;
    return EOK;
}

god_error_t god_fiber_suspend(void) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
    if (god_unlikely(cur_scheduler->dispatch_fiber == nil)) {
        return -1; //TODO：INROOTFIBER;
    }

    god_fiber_ptr cur_fiber = cur_scheduler->cur_fiber;
#ifndef _GOD_NDEBUG_
    assert(cur_fiber->scheduler == cur_scheduler);
#endif
    {
#ifdef STABLE_SCHEDULER
        god_fiber_ptr next_fiber = cur_scheduler->dispatch_fiber;
#else
        god_fiber_ptr next_fiber = god_invalid_fiber;
        if (god_unlikely(god_list_empty(&cur_scheduler->list))) {
            next_fiber = cur_scheduler->dispatch_fiber;
        } else {
            next_fiber = god_list_data(god_list_front(&cur_scheduler->list), god_fiber_t, node);
            god_list_pop_front(&cur_scheduler->list);
        }
#endif

        cur_fiber->state = god_fiber_state_suspended;
        god_swap_context(&cur_fiber->context, next_fiber->context, (god_intptr_t)next_fiber, false);
    }
#ifndef STABLE_SCHEDULER
    if (god_unlikely(cur_scheduler->cur_fiber->state == god_fiber_state_stopped)) {
        //god_list_erase(&cur_scheduler->cur_fiber->all_node);
        delete_fiber(cur_scheduler->cur_fiber);
    }
#endif
    cur_fiber->state = god_fiber_state_running;
    cur_scheduler->cur_fiber = cur_fiber;
    return EOK;
}

god_error_t god_fiber_resume(god_fiber_ptr f) {
    god_fiber_scheduler_ptr cur_scheduler = g_scheduler;
    assert(cur_scheduler != god_invalid_fiber_scheduler);
    if (god_unlikely(cur_scheduler == god_invalid_fiber_scheduler)) {
        return -1; //TODO：NOFIBERSCHED;
    }
#ifndef _GOD_NDEBUG_
    assert(f->scheduler == cur_scheduler);
#endif
    god_list_push_back(&cur_scheduler->list, &f->node);
    return EOK;
}

