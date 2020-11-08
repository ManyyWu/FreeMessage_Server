#include "run_test.h"
#include "fm_common/include/map.h"

typedef struct mynode_s {
  FM_MAP_NODE(mynode_s) node;
  int data;
} mynode_t;

FM_MAP_DEFINE(mymap1_s, mynode_s);
FM_MAP_PROTOTYPE_STATIC(mymap1_s, mynode_s, node, int)
FM_MAP_GENERATE_STATIC(mymap1_s, mynode_s, node, int, data)

typedef struct mymap1_s mymap1_t;

void
test1 (void) {
#define NODES_NUM 30
  mymap1_t m = FM_MAP_INITIALIZER();
  mynode_t *pos, *temp;
  mynode_t *n;
  mynode_t nodes[NODES_NUM];
  int i;

  for (i = 0; i < NODES_NUM; ++i) {
    FM_MAP_NODE_INIT(nodes[i].node);
    nodes[i].data = rand() % 100000;
    //printf("%d ", nodes[i].data);
  }
  //printf("\n");

  for (i = 0; i < NODES_NUM; ++i) {
    n = FM_MAP_INSERT(mymap1_s, &m, &nodes[i]);
    assert(!n);
  }

  FM_MAP_FOREACH_SAFE(pos, mymap1_s, &m, temp) {
    //printf("%d ", pos->data);
  }
  //printf("\nsize: %d\n", (int)FM_MAP_SIZE(&m));
  //printf("size: %d %s exist\n", nodes[0].data, FM_MAP_FIND(mymap1_s, &m, nodes[0].data) ? "is" : "is not");

  FM_MAP_FOREACH_SAFE(pos, mymap1_s, &m, temp) {
    if (pos->data % 2 == 0) {
      FM_MAP_REMOVE(mymap1_s, &m, pos);
      FM_MAP_NODE_INIT(pos->node);
      //printf("remove %d\n", pos->data);
    }
  }

  FM_MAP_FOREACH_SAFE(pos, mymap1_s, &m, temp) {
    //printf("%d ", pos->data);
  }
  //printf("\nsize: %d\n\n", (int)FM_MAP_SIZE(&m));

  FM_MAP_FOREACH_SAFE(pos, mymap1_s, &m, temp) {
    FM_MAP_REMOVE(mymap1_s, &m, pos);
    FM_MAP_NODE_INIT(pos->node);
  }
}

int
mycompare (mynode_t *n1, mynode_t *n2) {
  if (n1->data == n2->data)
    return 0;
  return (n1->data > n2->data ? 1 : -1);
}

FM_MAP_DEFINE(mymap2_s, mynode_s);
FM_MAP_PROTOTYPE_STATIC_CB(mymap2_s, mynode_s, node, mycompare);
FM_MAP_GENERATE_STATIC_CB(mymap2_s, mynode_s, node, mycompare)

typedef struct mymap2_s mymap2_t;

void
test2 (void) {
#define NODES_NUM 30
  mymap2_t m = FM_MAP_INITIALIZER();
  mynode_t *pos, *temp;
  mynode_t *n;
  mynode_t nodes[NODES_NUM];
  int i;

  for (i = 0; i < NODES_NUM; ++i) {
    FM_MAP_NODE_INIT(nodes[i].node);
    nodes[i].data = rand() % 100000;
    //printf("%d ", nodes[i].data);
  }
  //printf("\n");

  for (i = 0; i < NODES_NUM; ++i) {
    n = FM_MAP_INSERT(mymap2_s, &m, &nodes[i]);
    assert(!n);
  }

  FM_MAP_FOREACH_SAFE(pos, mymap2_s, &m, temp) {
    //printf("%d ", pos->data);
  }
  //printf("\nsize: %d\n", (int)FM_MAP_SIZE(&m));
  //printf("size: %d %s exist\n", nodes[0].data, FM_MAP_FIND(mymap2_s, &m, &nodes[0]) ? "is" : "is not");

  FM_MAP_FOREACH_SAFE(pos, mymap2_s, &m, temp) {
    if (pos->data % 2 == 0) {
      FM_MAP_REMOVE(mymap2_s, &m, pos);
      FM_MAP_NODE_INIT(pos->node);
      //printf("remove %d\n", pos->data);
    }
  }

  FM_MAP_FOREACH_SAFE(pos, mymap2_s, &m, temp) {
    //printf("%d ", pos->data);
  }
  //printf("\nsize: %d\n\n", (int)FM_MAP_SIZE(&m));

  FM_MAP_FOREACH_SAFE(pos, mymap2_s, &m, temp) {
    FM_MAP_REMOVE(mymap2_s, &m, pos);
    FM_MAP_NODE_INIT(pos->node);
  }
}

UNIT_TEST(map) {
  test1();
  test2();
}
