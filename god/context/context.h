#pragma once

#include <god/base/type.h>

#ifdef	__cplusplus
extern "C" {
#endif

struct god_context_detail;

typedef struct god_context_detail * god_context_t;

typedef void (* god_context_entry_t)(god_intptr_t);

#define god_invalid_context (god_context_t)0

god_intptr_t god_swap_context(god_context_t *from, god_context_t to, god_intptr_t arg, bool preserve_fpu/* = false*/);

god_context_t god_make_context(void *sp, god_size_t size, god_context_entry_t entry);

#ifdef	__cplusplus
}
#endif

