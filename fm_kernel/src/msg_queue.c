#include "msg_queue.h"
#include <assert.h>

void
fm_msg_queue_init (fm_msgq_t *q) {
  assert(q);

  FM_INIT_LIST_HEAD(&q->head);
  q->size = 0;
}

void
fm_msg_queue_destroy (fm_msgq_t *q) {
  assert(q);

  fm_msg_queue_clear(q);
}

void
fm_msg_queue_push (fm_msgq_t *q, fm_msg_t *msg) {
  assert(q && msg);
  assert(fm_list_count_entries(&q->head) == q->size);

  fm_list_add_tail(&msg->node, &q->head);
  q->size++;
}

fm_msg_t *
fm_msg_queue_pop (fm_msgq_t *q) {
  fm_list_head_t *head;

  assert(q);
  assert(fm_list_count_entries(&q->head) == q->size);

  if (fm_list_empty(&q->head))
    return NULL;
  head = q->head.next;
  fm_list_del_init(head);
  q->size--;
  return fm_list_entry(head, fm_msg_t, node);
}

fm_msg_t *
fm_msg_queue_peek (fm_msgq_t *q) {
  assert(q);

  return fm_list_first_entry(&q->head, fm_msg_t, node);
}

size_t
fm_msg_queue_size (fm_msgq_t *q) {
  assert(q);
  assert(fm_list_count_entries(&q->head) == q->size);

  return q->size;
}

void
fm_msg_queue_clear (fm_msgq_t *q) {
  int size;
  fm_list_head_t *pos, *next;

  assert(q);
  size = 0;
  fm_list_for_each_safe(pos, next, &q->head) {
    fm_list_del_init(pos);
    size++;
  }
  assert(size == q->size);
  q->size = 0;
}
