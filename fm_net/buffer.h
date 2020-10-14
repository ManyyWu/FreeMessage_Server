#ifndef FM_BUFFER_H
#define FM_BUFFER_H

#include "fm_common/define.h"

typedef struct fm_buf_s {
  void *data;
  int len;
  int size;
} fm_buf_t;

#endif
