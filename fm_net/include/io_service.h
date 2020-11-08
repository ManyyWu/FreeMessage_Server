#ifndef FM_IO_SERVICE_H
#define FM_IO_SERVICE_H

#include "fm_common/include/map.h"
#include "net.h"

#ifndef NDEBUG
#include <assert.h>
#endif

typedef struct fm_tcp_s {
  FM_MAP_NODE(fm_tcp_s) node;
  uv_tcp_t              ctx;
} fm_tcp_t;

/* fm_tcp_map_t<uint64_t, fm_tcp_t> */
FM_MAP_DEFINE(fm_tcp_map_s, fm_tcp_s);
typedef struct fm_tcp_map_s fm_tcp_map_t;

typedef struct fm_io_service_s {
  char                    name[IO_SERVICE_NAME_LEN];
  int                     type;
  int                     flags;
  fm_io_service_config_t *config;
  fm_tcp_map_t           *connections;
} fm_io_service_t;

enum {
  FM_NET_
  FM_IO_SERVICE_TCP_CLIENT  = 0x10,
  FM_IO_SERVICE_TCP_SERVER  = 0x11,
  FM_IO_SERVICE_UDP_CLIENT  = 0x20,
  FM_IO_SERVICE_UDP_SERVER  = 0x21,
  FM_IO_SERVICE_PIPE_CLIENT = 0x40,
  FM_IO_SERVICE_PIPE_SERVER = 0x41,
};

int
fm_io_service_init (fm_io_service_t *s, fm_io_service_config_t *conf);

int
fm_io_service_destroy (fm_io_service_t *s);

#endif
