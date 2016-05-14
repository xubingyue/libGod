#include <stdio.h>

#include <god/base/forward_list.h>
#include <god/base/type.h>

typedef struct {
    god_int32_t a;
    god_forward_list_node_t node;
    god_int32_t b;
} demo;

void demo_init(demo *val) {
    val->a = 0;
    god_forward_list_node_init(&val->node);
    val->b = 0;
}

void demo_destroy(demo *val) {
}

void print(const god_forward_list_t *l) {
    god_forward_list_node_t *node;
    for (node = god_forward_list_begin(l); node != god_forward_list_end(l); node = god_forward_list_next(node)) {
        demo *d = god_forward_list_data(node, demo, node);
        printf("(%d %d)", d->a, d->b);
    }
    printf("\n");
}

god_int32_t main(god_int32_t argc, char *argv[]) {
    god_forward_list_t l;
    god_forward_list_init(&l);
    if (god_forward_list_empty(&l)) {
        printf("empty\n");
    }
    demo d1;
    demo_init(&d1);
    d1.a = 1;
    god_forward_list_insert_after(god_forward_list_before_begin(&l), &d1.node);
    print(&l);
    demo d2;
    demo_init(&d2);
    d2.a = 2;
    god_forward_list_push_front(&l, &d2.node);
    print(&l);

    god_forward_list_node_t *node = god_forward_list_front(&l);
    demo *d = god_forward_list_data(node, demo, node);
    printf("front: (%d %d)\n", d->a, d->b);

    god_forward_list_erase_after(god_forward_list_begin(&l));
    print(&l);
    god_forward_list_pop_front(&l);
    print(&l);
    return 0;
}

