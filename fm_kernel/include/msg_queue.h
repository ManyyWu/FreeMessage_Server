#ifndef FM_MSGQ_H
#define FM_MSGQ_H

#include "fm_common/include/list.h"
#include "msg.h"

typedef struct fm_msgq_s {
  fm_list_head_t head;
  size_t         size;
} fm_msgq_t;

void
fm_msg_queue_init (fm_msgq_t *q);

void
fm_msg_queue_destroy (fm_msgq_t *q);

void
fm_msg_queue_push (fm_msgq_t *q, fm_msg_t *msg);

fm_msg_t *
fm_msg_queue_pop (fm_msgq_t *q);

fm_msg_t *
fm_msg_queue_peek (fm_msgq_t *q);

size_t
fm_msg_queue_size (fm_msgq_t *q);

void
fm_msg_queue_clear (fm_msgq_t *q);

#endif