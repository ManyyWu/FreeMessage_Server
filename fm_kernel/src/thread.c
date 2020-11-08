#include "thread.h"

#include <bits/local_lim.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int
fm_mutex_init (fm_mutex_t *mutex) {
  assert(mutex);
#if defined(NDEBUG) || !defined(PTHREAD_MUTEX_ERRORCHECK)
  return pthread_mutex_init(mutex, NULL);
#else
  int err;
  pthread_mutexattr_t attr;

  if (pthread_mutexattr_init(&attr)
      || pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK))
    abort();

  err = pthread_mutex_init(mutex, &attr);

  if (pthread_mutexattr_destroy(&attr))
    abort();

  return err;
#endif
}

int
fm_recursive_mutex_init (fm_mutex_t *mutex) {
  int err;
  pthread_mutexattr_t attr;

  if (pthread_mutexattr_init(&attr)
      || pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
    abort();

  err = pthread_mutex_init(mutex, &attr);

  if (pthread_mutexattr_destroy(&attr))
    abort();

  return err;
}

void
fm_mutex_destroy (fm_mutex_t *mutex) {
  if (pthread_mutex_destroy(mutex))
    abort();
}

void
fm_mutex_lock (fm_mutex_t *mutex) {
  if (pthread_mutex_lock(mutex))
    abort();
}

void
fm_mutex_unlock (fm_mutex_t *mutex) {
  if (pthread_mutex_unlock(mutex))
    abort();
}

int
fm_mutex_trylock (fm_mutex_t *mutex) {
  int err;

  err = pthread_mutex_trylock(mutex);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return EBUSY;
    abort();
  }

  return 0;
}

/* rwlock */
int
fm_rwlock_init (fm_rwlock_t *rwlock) {
  return pthread_rwlock_init(rwlock, NULL);
}

void
fm_rwlock_destroy (fm_rwlock_t *rwlock) {
  if (pthread_rwlock_destroy(rwlock))
    abort();
}

void
fm_rwlock_rdlock (fm_rwlock_t *rwlock) {
  if (pthread_rwlock_rdlock(rwlock))
    abort();
}

void
fm_rwlock_rdunlock (fm_rwlock_t *rwlock) {
  if (pthread_rwlock_unlock(rwlock))
    abort();
}

int
fm_rwlock_rdtrylock (fm_rwlock_t *rwlock) {
  int err;

  err = pthread_rwlock_tryrdlock(rwlock);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return EBUSY;
    abort();
  }
  return 0;
}

void
fm_rwlock_wrlock (fm_rwlock_t *rwlock) {
  if (pthread_rwlock_wrlock(rwlock))
    abort();
}

void
fm_rwlock_wrunlock (fm_rwlock_t *rwlock) {
  if (pthread_rwlock_unlock(rwlock))
    abort();
}

int
fm_rwlock_wrtrylock (fm_rwlock_t* rwlock) {
  int err;

  err = pthread_rwlock_trywrlock(rwlock);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return EBUSY;
    abort();
  }

  return 0;
}

int
fm_cond_init (fm_cond_t* cond) {
#if defined(FM_SYSTEM_DARWIN)
  return pthread_cond_init(cond, NULL);
#else
  /* Using monotonic time */

  int err;
  pthread_condattr_t attr;

  if (pthread_condattr_init(&attr)
      || pthread_condattr_setclock(&attr, CLOCK_MONOTONIC))
    abort();

  err = pthread_cond_init(cond, &attr);

  if (pthread_condattr_destroy(&attr))
    abort();

  return err;
#endif
}

void
fm_cond_destroy (fm_cond_t* cond) {
#if defined(FM_SYSTEM_DARWIN)
  /* It has been reported that destroying condition variables that have been
   * signalled but not waited on can sometimes result in application crashes.
   * See https://codereview.chromium.org/1323293005.
   */
  int err;
  pthread_mutex_t mutex;
  struct timespec ts;

  if (pthread_mutex_init(&mutex, NULL)
      || pthread_mutex_lock(&mutex))
    abort();

  ts.tv_sec = 0;
  ts.tv_nsec = 1;

  err = pthread_cond_timedwait_relative_np(cond, &mutex, &ts);
  if (err && ETIMEDOUT != err)
    abort();

  if (pthread_mutex_unlock(&mutex)
      || pthread_mutex_destroy(&mutex))
    abort();
#else
  if (pthread_cond_destroy(cond))
    abort();
#endif
}

void
fm_cond_signal (fm_cond_t* cond) {
  if (pthread_cond_signal(cond))
    abort();
}

void
fm_cond_broadcast (fm_cond_t* cond) {
  if (pthread_cond_broadcast(cond))
    abort();
}

void
fm_cond_wait (fm_cond_t* cond, fm_mutex_t* mutex) {
  if (pthread_cond_wait(cond, mutex))
    abort();
}

int
fm_cond_timedwait (fm_cond_t* cond, fm_mutex_t* mutex, fm_ns_t timeout) {
  int err;
  struct timespec ts;

  timeout += fm_monotonic_time(0);
  FM_NS_TO_TIMESPEC(ts, timeout);

#if defined(FM_SYSTEM_DARWIN)
  err = pthread_cond_timedwait_relative_np(cond, mutex, &ts);
#else
  err = pthread_cond_timedwait(cond, mutex, &ts);
  if (err && ETIMEDOUT != err)
    abort();
#endif

  return err;
}

int
fm_barrier_init (fm_barrier_t* barrier, uint32_t count) {
  return pthread_barrier_init(barrier, NULL, count);
}

void
fm_barrier_destroy (fm_barrier_t* barrier) {
  if (pthread_barrier_destroy(barrier))
    abort();
}

void
fm_barrier_wait_and_destroy (fm_barrier_t* barrier) {
  if (fm_barrier_wait(barrier))
    fm_barrier_destroy(barrier);
}

int
fm_barrier_wait (fm_barrier_t* barrier) {
  int err;

  err = pthread_barrier_wait(barrier);
  if (err && PTHREAD_BARRIER_SERIAL_THREAD != err)
    abort();

  return (err == PTHREAD_BARRIER_SERIAL_THREAD);
}

int
fm_sem_init (fm_sem_t* sem, unsigned int value) {
  return sem_init(sem, 0, value) ? errno : 0;
}

void
fm_sem_destroy (fm_sem_t* sem) {
  if (sem_destroy(sem))
    abort();
}

void
fm_sem_post (fm_sem_t* sem) {
  if (sem_post(sem))
    abort();
}

void
fm_sem_wait (fm_sem_t* sem) {
  int err;

  while ((err = sem_wait(sem)) < 0 && EINTR == errno)
    ;

  if (err < 0)
    abort();
}

int
fm_sem_trywait (fm_sem_t* sem) {
  int err;

  while ((err = sem_trywait(sem) < 0 && EINTR == errno))
    ;

  if (err < 0 && EAGAIN != errno)
    abort();

  return errno;
}

int
fm_thread_create (fm_thread_t* t, fm_thread_entry entry, void* args,
                  size_t stack_size) {
  int err;
  pthread_attr_t attr;
  pthread_attr_t* attr_inited;
  size_t page_size;

  if (!entry)
    return EINVAL;

  attr_inited = NULL;
  if (stack_size > 0) {
    page_size = getpagesize();
    stack_size = (stack_size + page_size - 1) & ~(page_size - 1);
#if defined(PTHREAD_STACK_MIN)
    if (stack_size < PTHREAD_STACK_MIN)
      stack_size = PTHREAD_STACK_MIN;
#endif
    if (pthread_attr_init(&attr)
        || pthread_attr_setstacksize(&attr, stack_size))
      abort();
    attr_inited = &attr;
  }

  err = pthread_create(t, attr_inited, (void* (*)(void*))entry, args);

  if (attr_inited && pthread_attr_destroy(attr_inited))
    abort();

  return err;
}

fm_thread_t
fm_thread_self (void) {
  return pthread_self();
}

fm_tid_t
fm_thread_tid (void) {
  return syscall(SYS_gettid);
}

int
fm_thread_join (const fm_thread_t* t) {
  return pthread_join(*t, NULL);
}

int
fm_thread_equal (const fm_thread_t* t1, const fm_thread_t* t2) {
  return pthread_equal(*t1, *t2);
}

void
fm_sleep (fm_ms_t ms) {
  int err;
  struct timespec ts;

  FM_MS_TO_TIMESPEC(ts, ms);
  while ((err = nanosleep(&ts, &ts)) < 0 && EINTR == errno)
    ;

  assert(0 == err);
}

void
fm_once (fm_once_t *once, void (*callback)(void)) {
  if (pthread_once(once, callback))
    abort();
}
