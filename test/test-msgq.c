#include "run_test.h"
#include "fm_kernel/include/msg_queue.h"

UNIT_TEST(msgq) {
#define NODE_NUM 20
  int i;
  fm_msg_t nodes[NODE_NUM];
  fm_list_head_t *pos, *next;
  fm_msgq_t q;
  fm_msg_t *top;
  fm_msg_t *p[NODE_NUM];

  for (i = 0; i < NODE_NUM; ++i) {
    FM_INIT_LIST_HEAD(&nodes[i].node);
    nodes[i].service = i;
    p[i] = &nodes[i];
  }

  fm_msg_queue_init(&q);
  assert_true(!fm_msg_queue_size(&q));
  for (i = 0; i < NODE_NUM; ++i) {
    fm_msg_queue_push(&q, &nodes[i]);
  }
  assert_true(fm_msg_queue_size(&q) == NODE_NUM);
  fm_msg_t *a = fm_msg_queue_peek(&q);
  assert_true(fm_list_entry_is_first(&a->node, &q.head));

  i = 0;
  printf(">> ");
  fm_list_for_each_safe(pos, next, &q.head) {
    fm_msg_t *entry = fm_list_entry(pos, fm_msg_t, node);
    assert_true(pos && entry);
    assert_int_equal(i, entry->service);
    printf("%d ", entry->service);
    ++i;
  }
  printf("\n");

  i = NODE_NUM - 1;
  printf(">> ");
  fm_list_for_each_backwardly(pos, &q.head) {
    fm_msg_t *entry = fm_list_entry(pos, fm_msg_t, node);
    assert_true(pos && entry);
    assert_int_equal(i, entry->service);
    printf("%d ", entry->service);
    --i;
  }
  printf("\n");

  printf(">> ");
  while ((top = fm_msg_queue_pop(&q)))
    printf("%d ", top->service);
  printf("\n");

  assert_true(fm_list_empty(&q.head));
  fm_msg_queue_destroy(&q);
}
