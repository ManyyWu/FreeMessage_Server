#include "run_test.h"
#include "fm_common/include/list.h"

struct node {
  fm_list_head_t head;
  int index;
};

UNIT_TEST(doubly_list) {
#define NODE_NUM 20
  int i;
  struct node nodes[NODE_NUM];
  struct node *p[NODE_NUM];
  fm_list_head_t *pos, *next;
  FM_LIST_HEAD(l);

  for (i = 0; i < NODE_NUM; ++i) {
    FM_INIT_LIST_HEAD(&nodes[i].head);
    nodes[i].index = i;
    p[i] = &nodes[i];
  }

  assert_true(fm_list_empty(&l));
  for (i = 0; i < NODE_NUM; ++i) {
    fm_list_add_tail(&nodes[i].head, &l);
  }
  assert_true(!fm_list_empty(&l));
  assert_int_equal(fm_list_count_entries(&l), NODE_NUM);

  assert_true(fm_list_entry_is_first(&nodes[0].head, &l));
  assert_true(fm_list_entry_is_last(&nodes[NODE_NUM - 1].head, &l));

  i = 0;
  printf(">> ");
  fm_list_for_each_safe(pos, next, &l) {
    struct node *entry = fm_list_entry(pos, struct node, head);
    assert_true(pos && entry);
    assert_int_equal(i, entry->index);
    printf("%d ", entry->index);
    ++i;
  }
  printf("\n");

  i = NODE_NUM - 1;
  printf(">> ");
  fm_list_for_each_backwardly(pos, &l) {
    struct node *entry = fm_list_entry(pos, struct node, head);
    assert_true(pos && entry);
    assert_int_equal(i, entry->index);
    printf("%d ", entry->index);
    --i;
  }
  printf("\n");

  fm_list_for_each_safe(pos, next, &l) {
    fm_list_del_init(pos);
  }
  assert_true(fm_list_empty(&l));
}
