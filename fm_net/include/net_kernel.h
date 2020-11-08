#ifndef FM_NET_KERNEL_H
#define FM_NET_KERNEL_H

#include "io_context.h"

struct fm_io_context_s;

typedef struct fm_net_kernel_s {
  struct fm_io_context_s *ctxs;
  int                     nctxs;
} fm_net_kernel_t;

#endif
