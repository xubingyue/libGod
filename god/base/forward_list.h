#pragma once

#include <god/base/predef.h>
#include <god/base/type.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct god_forward_list_node god_forward_list_node_t;

struct god_forward_list_node {
    god_forward_list_node_t *_next;
};

#define god_forward_list_node_init(__node) \
    (__node)->_next = nil

#define god_forward_list_node_destroy(__node)

typedef struct god_forward_list god_forward_list_t;

struct god_forward_list {
    god_forward_list_node_t _node;
};

#define god_forward_list_init(__list) \
    (__list)->_node._next = nil

#define god_forward_list_destroy(__list)

#define god_forward_list_empty(__list) \
    ((__list)->_node._next == nil)

#define god_forward_list_swap(__lista, __listb) \
    ({ \
        god_forward_list_node_t __tmp = (__lista)->_node; \
        (__lista)->_node = (__listb)->_node; \
        (__listb)->_node = __tmp; \
    })

#define god_forward_list_clear(__list) \
    (__list)->_node._next = nil

#define god_forward_list_front(__list) god_forward_list_before_begin(__list)->_next

inline static void god_forward_list_insert_after(god_forward_list_node_t *__position_node, god_forward_list_node_t *__node) {
    __node->_next = __position_node->_next;
    __position_node->_next = __node;
}

#define god_forward_list_push_front(__list, __node) \
    god_forward_list_insert_after(god_forward_list_before_begin(__list), __node)

inline static void god_forward_list_erase_after(god_forward_list_node_t *__node) {
    __node->_next = __node->_next->_next;
}

#define god_forward_list_pop_front(__list) \
    god_forward_list_erase_after(god_forward_list_before_begin(__list))

// iteration
#define god_forward_list_before_begin(__list) (&(__list)->_node)

#define god_forward_list_begin(__list) (__list)->_node._next

#define god_forward_list_end(__list) nil

#define god_forward_list_next(__node) (__node)->_next

#define god_forward_list_data(__node, __type, __member) \
    (__type *)((god_byte_t *)(__node) - god_offsetof(__type, __member))

#ifdef	__cplusplus
}
#endif

