#ifndef FM_BUFFER_H
#define FM_BUFFER_H

typedef struct fm_buf_s {
  int   lenght;
  int   size;
  void *data;
} fm_buf_t;

#endif
