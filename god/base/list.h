#pragma once

#include <god/base/predef.h>
#include <god/base/type.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct god_list_node god_list_node_t;

struct god_list_node {
    god_list_node_t *_prev;
    god_list_node_t *_next;
};

#define god_list_node_init(__node) \
    (__node)->_prev = nil; \
    (__node)->_next = nil

#define god_list_node_destroy(__node)

typedef struct god_list god_list_t;

struct god_list {
    god_list_node_t _node;
};

#define god_list_init(__list) \
    (__list)->_node._prev = &(__list)->_node; \
    (__list)->_node._next = &(__list)->_node

#define god_list_destroy(__list)

#define god_list_empty(__list) \
    ((__list)->_node._next == &(__list)->_node)

#define god_list_swap(__lista, __listb) \
    ({ \
        god_list_node_t __tmp = (__lista)->_node; \
        (__lista)->_node = (__listb)->_node; \
        (__listb)->_node = __tmp; \
    })

#define god_list_clear(__list) \
    (__list)->_node._prev = &(__list)->_node; \
    (__list)->_node._next = &(__list)->_node

#define god_list_front(__list) ((__list)->_node._next)

#define god_list_back(__list) ((__list)->_node._prev)

inline static void god_list_insert(god_list_node_t *__position_node, god_list_node_t *__node) {
    __node->_next = __position_node;
    __node->_prev = __position_node->_prev;
    __position_node->_prev->_next = __node;
    __position_node->_prev = __node;
}

#define god_list_push_front(__list, __node) god_list_insert((__list)->_node._next, __node)

#define god_list_push_back(__list, __node) god_list_insert(&(__list)->_node, __node)

inline static void god_list_erase(god_list_node_t *__node) {
    __node->_next->_prev = __node->_prev;
    __node->_prev->_next = __node->_next;
    __node->_prev = nil;
    __node->_next = nil;
}

#define god_list_pop_front(__list) god_list_erase((__list)->_node._next)

#define god_list_pop_back(__list) god_list_erase((__list)->_node._prev)

// iteration
#define god_list_begin(__list) (__list)->_node._next

#define god_list_end(__list) (&(__list)->_node)

#define god_list_next(__node) (__node)->_next

#define god_list_prev(__node) (__node)->_prev

// reverse iteration
#define god_list_rbegin(__list) (__list)->_node._prev

#define god_list_rend(__list) (&(__list)->_node)

#define god_list_rnext(__node) (__node)->_prev

#define god_list_rprev(__node) (__node)->_next

#define god_list_data(__node, __type, __member) \
    (__type *)((god_byte_t *)(__node) - god_offsetof(__type, __member))

#ifdef	__cplusplus
}
#endif

