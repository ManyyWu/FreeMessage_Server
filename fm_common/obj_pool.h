#ifndef FM_OBJ_POOL_H
#define FM_OBJ_POOL_H

#include "fm_kernel/thread.h"

#define FM_OBJPOOL fm_obj_pool_t

typedef struct fm_obj_pool_s {
  int size;
  int obj_size;
  int max_size;
  void *pool;
  fm_mutex_t mutex;
} fm_obj_pool_t;

int
fm_obj_pool_init (FM_OBJPOOL *p, int init_size, int max_size);

int
fm_obj_pool_close (FM_OBJPOOL *p);

int
fm_obj_pool_clear (FM_OBJPOOL *p);

void *
fm_obj_pool_pop (FM_OBJPOOL *p);

int
fm_obj_pool_push (FM_OBJPOOL *p, void *obj);

void
fm_obj_pool_get_size (FM_OBJPOOL *p, int *size, int *capacity);

int
fm_obj_pool_adjust (FM_OBJPOOL *p);

int
fm_obj_pool_try_lock (FM_OBJPOOL *p);

int
fm_obj_pool_lock (FM_OBJPOOL *p);

int
fm_obj_pool_unlock (FM_OBJPOOL *p);

#endif
