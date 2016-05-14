#include <stdio.h>

#include <god/base/queue.h>
#include <god/base/type.h>

typedef struct {
    god_int32_t a;
    god_queue_node_t node;
    god_int32_t b;
} demo;

void demo_init(demo *val) {
    val->a = 0;
    god_queue_node_init(&val->node);
    val->b = 0;
}

void demo_destroy(demo *val) {
}

void print(const god_queue_t *l) {
    god_queue_node_t *node;
    for (node = god_queue_begin(l); node != god_queue_end(l); node = god_queue_next(node)) {
        demo *d = god_queue_data(node, demo, node);
        printf("(%d %d)", d->a, d->b);
    }
    printf("\n");
}

god_int32_t main(god_int32_t argc, char *argv[]) {
    god_queue_t l;
    god_queue_init(&l);
    if (god_queue_empty(&l)) {
        printf("empty\n");
    }
    demo d1;
    demo_init(&d1);
    d1.a = 1;
    god_queue_push(&l, &d1.node);
    print(&l);
    demo d2;
    demo_init(&d2);
    d2.a = 2;
    god_queue_push(&l, &d2.node);
    print(&l);

    god_queue_node_t *node = god_queue_front(&l);
    demo *d = god_queue_data(node, demo, node);
    printf("front: (%d %d)\n", d->a, d->b);

    node = god_queue_back(&l);
    d = god_queue_data(node, demo, node);
    printf("back: (%d %d)\n", d->a, d->b);

    god_queue_pop(&l);
    print(&l);
    god_queue_pop(&l);
    print(&l);
    return 0;
}

