#pragma once

#include <god/base/error.h>
#include <god/base/list.h>
#include <god/base/type.h>
#include <god/context/context.h>

#ifdef	__cplusplus
extern "C" {
#endif

struct god_fiber;
struct god_fiber_scheduler;

typedef struct god_fiber * god_fiber_ptr;

typedef void (* god_fiber_entry_t)(god_intptr_t);

typedef struct god_fiber_scheduler * god_fiber_scheduler_ptr;

#define god_invalid_fiber nil
#define god_invalid_fiber_scheduler nil

//god_fiber_scheduler_ptr god_fiber_scheduler_self(void);

god_error_t god_fiber_scheduler_init(void);

god_error_t god_fiber_scheduler_destroy(void);

god_error_t god_fiber_scheduler_dispatch(void);

god_fid_t god_fiber_id(void);

god_fiber_ptr god_fiber_self(void);

god_error_t god_fiber_create(god_fiber_ptr *fiber, god_fiber_entry_t entry, god_intptr_t param);

god_error_t god_fiber_yield(void);

god_error_t god_fiber_suspend(void);

god_error_t god_fiber_resume(god_fiber_ptr f);

#ifdef	__cplusplus
}
#endif

