#ifndef FM_MSG_H
#define FM_MSG_H

#include "fm_common/list.h"

typedef struct fm_msg_s {
  struct list_head head;
  fm_buf_t buf;
  int type;
} fm_msg_t;

#endif
