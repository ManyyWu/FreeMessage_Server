#ifndef FM_MSG_H
#define FM_MSG_H

#include "fm_common/include/define.h"
#include "fm_common/include/buffer.h"
#include "fm_common/include/list.h"

typedef struct fm_msg_s {
  fm_list_head_t node;
  uint16_t       service;
  uint32_t       type;
  uint32_t       length;
  char           data[1];
} fm_msg_t;

fm_msg_t *
fm_msg_create (uint32_t length);

void
fm_msg_destroy (fm_msg_t **msg);

#endif
