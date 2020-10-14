#ifndef FM_NET_H
#define FM_NET_H

#include <netinet/in.h>

typedef struct fm_net_addr_s {
  char addr[INET6_ADDRSTRLEN];
  uint16_t port;
} fm_net_addr_t;

typedef struct fm_server_net_s {
  int index;
  fm_net_addr_t addr;
} fm_server_net_t;

union fm_net_id_u {
  uint64_t id;
  struct u {
    int index;
    int id;
  };
};

#endif
