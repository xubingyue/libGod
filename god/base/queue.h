#pragma once

#include <god/base/predef.h>
#include <god/base/type.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct god_queue_node god_queue_node_t;

struct god_queue_node {
    god_queue_node_t *_next;
};

#define god_queue_node_init(__node) \
    (__node)->_next = nil

#define god_queue_node_destroy(__node)

typedef struct god_queue god_queue_t;

struct god_queue {
    god_queue_node_t _node;
    god_queue_node_t *_back;
};

#define god_queue_init(__list) \
    (__list)->_node._next = nil; (__list)->_back = &(__list)->_node

#define god_queue_destroy(__list)

#define god_queue_empty(__list) \
    ((__list)->_node._next == nil)

#define god_queue_swap(__lista, __listb) \
    ({ \
        god_queue_node_t __tmp = (__lista)->_node; \
        (__lista)->_node = (__listb)->_node; \
        (__listb)->_node = __tmp; \
        \
        god_queue_node_t *__tmpback = (__lista)->_back; \
        (__lista)->_back = (__listb)->_back; \
        (__listb)->_back = __tmpback; \
    })

#define god_queue_clear(__list) \
    (__list)->_node._next = nil; (__list)->_back = &(__list)->_node

#define god_queue_front(__list) ((__list)->_node._next)

#define god_queue_back(__list) \
    ({ \
        god_queue_node_t *node = nil; \
        if (!god_queue_empty(__list)) { \
            node = (__list)->_back; \
        } \
        node; /* return current node */ \
    })

#define god_queue_push(__list, __node) \
    (__node)->_next = nil; \
    (__list)->_back->_next = (__node); \
    (__list)->_back = (__node)

#define god_queue_pop(__list) \
    ({ \
        god_queue_node_t *node = (__list)->_node._next; \
        (__list)->_node._next = node->_next; \
        if ((__list)->_back == node) \
        { \
            (__list)->_back = &(__list)->_node; \
        } \
    })

#define god_queue_begin(__list) (__list)->_node._next

#define god_queue_end(__list) nil

#define god_queue_next(__node) (__node)->_next

#define god_queue_data(__node, __type, __member) \
    (__type *)((god_byte_t *)(__node) - god_offsetof(__type, __member))

#ifdef	__cplusplus
}
#endif

