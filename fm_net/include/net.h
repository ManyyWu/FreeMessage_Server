#ifndef FM_NET_H
#define FM_NET_H

#include "uv.h"
#include "fm_common/include/list.h"

#include <netinet/in.h>

#define IO_CONTEXT_NAME_LEN    32
#define IO_SERVICE_NAME_LEN 32

#pragma pack(push, 1)
typedef struct fm_net_pkg_head_s {
/**
 * +---------2-------3--------5--------------+
 * | version | flags | length |      data    +
 * +-----------------------------------------+
 *
 * flags[0]:
 * flags[1]:
 * flags[2]:
 * flags[3]:
 * flags[4]:
 * flags[5]:
 * flags[6]:
 * flags[7]: extension bit, reserved
 **/

  uint16_t version;
  uint8_t  flags;
  uint16_t length;
} fm_net_pkg_head_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct fm_netbuf_s {
  fm_net_pkg_head_t head;
  char              data[1];
} fm_netpkg_t;
#pragma pack(pop)

enum {
  FM_NET_PKG_FLAG_0 = 0x01,
  FM_NET_PKG_FLAG_1 = 0x02,
  FM_NET_PKG_FLAG_2 = 0x04,
  FM_NET_PKG_FLAG_3 = 0x08,
  FM_NET_PKG_FLAG_4 = 0x10,
  FM_NET_PKG_FLAG_5 = 0x20,
  FM_NET_PKG_FLAG_6 = 0x40,
  FM_NET_PKG_FLAG_7 = 0x80,
  FM_NET_PKG_FLAG_EXT = FM_NET_PKG_FLAG_7,
};

typedef struct fm_interface_config_s {
} fm_io_service_config_t;

#define FM_IO_CTX_ID_MAX      0xffff
#define FM_IO_SERVICE_ID_MAX  0xffff
#define FM_FD_MAX             0x7fffffff
#define FM_IO_CTX_ID_MASK     0xffff000000000000
#define FM_IO_SERVICE_ID_MASK 0x0000ffff00000000
#define FM_FD_MASK            0x00000000ffffffff
#define FM_IO_CTX_BASE        48
#define FM_IO_SERVICE_BASE    32
#define FM_FD_BASE            0

/* id = io_ctx_id << 48 + io_service_id << 32 + fd */
#define FM_NID_CONBINE(io_ctx_id, io_service_id, fd)                                                \
  (((io_ctx_id) << FM_IO_CTX_BASE) | ((io_service_id) << FM_IO_SERVICE_BASE) | ((fd) << FM_FD_BASE))
#define FM_NID_PARSE_IO_CTX_ID(nid)                                                                 \
  (((nid) & FM_IO_CTX_ID_MASK) >> FM_IO_CTX_BASE)
#define FM_NID_PARSE_IO_SERVICE_ID(nid)                                                             \
  (((nid) & FM_IO_SERVICE_ID_MASK) >> FM_IO_SERVICE_BASE)
#define FM_NID_PARSE_FD_ID(nid)                                                                     \
  (((nid) & FM_FD_MASK) >> FM_FD_BASE)

#define CHECK_IO_CTX_ID(io_ctx_id)                                                                  \
  assert(io_ctx_id >= 0 && io_ctx_id <= FM_IO_CTX_ID_MAX)
#define CHECK_IO_SERVICE_ID(io_service_id)                                                          \
  assert(io_service_id >= 0 && io_service_id <= FM_IO_SERVICE_ID_MAX)
#define CHECK_FD_ID(fd)                                                                             \
  assert(fd >= 0 && fd <= FM_FD_MAX)

#endif
