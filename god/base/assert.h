#pragma once

#include <god/base/predef.h>

#include <assert.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef _GOD_NDEBUG_

#define god_assert(expr) ((void)0)
#define god_verify(expr) ((void)(expr))
#define god_notreach() abort()

#else

#define god_assert(expr) assert(expr)
#define god_verify(expr) assert(expr)
#define god_notreach() abort()

#endif

#ifdef	__cplusplus
}
#endif

