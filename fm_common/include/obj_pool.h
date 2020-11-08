#ifndef FM_OBJ_POOL_H
#define FM_OBJ_POOL_H

#include "fm_kernel/include/thread.h"

struct fm_obj_pool_s {
  int size;
  int obj_size;
  int max_size;
  void *pool;
  fm_mutex_t mutex;
} fm_obj_pool_t;

int
fm_obj_pool_init (fm_obj_pool_t *p, int init_size, int max_size);

int
fm_obj_pool_close (fm_obj_pool_t *p);

int
fm_obj_pool_clear (fm_obj_pool_t *p);

void *
fm_obj_pool_pop (fm_obj_pool_t *p);

int
fm_obj_pool_push (fm_obj_pool_t *p, void *obj);

void
fm_obj_pool_get_size (fm_obj_pool_t *p, int *size, int *capacity);

int
fm_obj_pool_adjust (fm_obj_pool_t *p);

int
fm_obj_pool_try_lock (fm_obj_pool_t *p);

int
fm_obj_pool_lock (fm_obj_pool_t *p);

int
fm_obj_pool_unlock (fm_obj_pool_t *p);

#endif
