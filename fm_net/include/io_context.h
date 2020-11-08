#ifndef FM_IO_CONTEXT_H
#define FM_IO_CONTEXT_H

#include "io_service.h"

struct fm_thread_s;

typedef struct fm_io_context_s {
  char                name[IO_CONTEXT_NAME_LEN];
  struct fm_thread_s *thread;
  uv_loop_t          *loop;
  fm_io_service_t *ifs;
  int                 nifs;
} fm_io_context_t;

#endif
