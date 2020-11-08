#include "msg.h"

#include <malloc.h>
#include <assert.h>

fm_msg_t *
fm_create_msg (uint32_t length) {
  return (fm_msg_t *)malloc(sizeof(fm_msg_t) - 1 + length);
}

void
fm_destroy_msg(fm_msg_t **msg) {
  assert(msg && *msg);

  free(*msg);
  *msg = NULL;
}
