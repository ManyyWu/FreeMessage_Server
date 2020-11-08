#include "run_test.h"
#include "fm_kernel/include/thread.h"

UNIT_TEST(mutex) {
  fm_mutex_t mutex;

  assert_int_equal(fm_mutex_init(&mutex), 0);
  fm_mutex_lock(&mutex);
  assert_int_equal(fm_mutex_trylock(&mutex), EBUSY);
  fm_mutex_unlock(&mutex);
  fm_mutex_destroy(&mutex);
}

UNIT_TEST(recursive_mutex) {
  fm_mutex_t mutex;

  assert_int_equal(fm_recursive_mutex_init(&mutex), 0);
  fm_mutex_lock(&mutex);
  fm_mutex_lock(&mutex);
  assert_int_equal(fm_mutex_trylock(&mutex), 0);
  fm_mutex_unlock(&mutex);
  fm_mutex_unlock(&mutex);
  fm_mutex_unlock(&mutex);
  fm_mutex_destroy(&mutex);
}

UNIT_TEST(rwlock) {
  fm_rwlock_t rwlock;

  fm_rwlock_init(&rwlock);
  fm_rwlock_wrlock(&rwlock);
  assert_int_equal(fm_rwlock_wrtrylock(&rwlock), EBUSY);
  assert_int_equal(fm_rwlock_rdtrylock(&rwlock), EBUSY);
  fm_rwlock_wrunlock(&rwlock);
  fm_rwlock_rdlock(&rwlock);
  assert_int_equal(fm_rwlock_wrtrylock(&rwlock), EBUSY);
  assert_int_equal(fm_rwlock_rdtrylock(&rwlock), 0);
  fm_rwlock_rdunlock(&rwlock);
  fm_rwlock_rdunlock(&rwlock);
  fm_rwlock_destroy(&rwlock);
}

static fm_barrier_t s_barrier;
static fm_mutex_t s_mutex;
static fm_cond_t s_cond;
static int s_n;

static void
cond_test_thread_proc (void *args) {
  fm_mutex_lock(&s_mutex);
  s_n++;
  fm_cond_signal(&s_cond);
  fm_mutex_unlock(&s_mutex);
}

static void
cond_test_thread_proc1 (void *args) {
  fm_mutex_lock(&s_mutex);
  s_n++;
  fm_cond_wait(&s_cond, &s_mutex);
  fm_mutex_unlock(&s_mutex);
  fm_cond_signal(&s_cond);
}

static void
cond_test_thread_proc2 (void *args) {
  fm_mutex_lock(&s_mutex);
  s_n++;
  fm_cond_wait(&s_cond, &s_mutex);
  fm_mutex_unlock(&s_mutex);
  fm_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(cond) {
#define THR_NUM 10
  int i;
  fm_thread_t t[THR_NUM];

  assert_int_equal(fm_mutex_init(&s_mutex), 0);
  assert_int_equal(fm_cond_init(&s_cond), 0);

  /* test 0 */
  s_n = 0;
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_create(&t[i], cond_test_thread_proc, NULL, 0), 0);

  fm_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    fm_cond_timedwait(&s_cond, &s_mutex, 1e6);
  fm_mutex_unlock(&s_mutex);
  assert_int_equal(s_n, THR_NUM);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_join(&t[i]), 0);

  /* test 1 */
  s_n = 0;
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_create(&t[i], cond_test_thread_proc1, NULL, 0), 0);

  fm_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    fm_cond_timedwait(&s_cond, &s_mutex, 1e6);
  fm_mutex_unlock(&s_mutex);
  fm_cond_signal(&s_cond);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_join(&t[i]), 0);

  /* test 2 */
  s_n = 0;
  fm_barrier_init(&s_barrier, THR_NUM + 1);
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_create(&t[i], cond_test_thread_proc2, NULL, 0), 0);

  fm_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    fm_cond_timedwait(&s_cond, &s_mutex, 1e6);
  fm_mutex_unlock(&s_mutex);
  fm_cond_broadcast(&s_cond);
  fm_barrier_wait_and_destroy(&s_barrier);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_join(&t[i]), 0);

  fm_mutex_destroy(&s_mutex);
  fm_cond_destroy(&s_cond);
}

static void
barrier_test_thread_proc (void *args) {
  fm_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(barrier) {
#undef THR_NUM
#define THR_NUM 10
  int i;
  fm_thread_t t[THR_NUM];

  fm_barrier_init(&s_barrier, THR_NUM + 1);
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_create(&t[i], barrier_test_thread_proc, NULL, 0), 0);

  fm_barrier_wait_and_destroy(&s_barrier);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(fm_thread_join(&t[i]), 0);
}

fm_sem_t s_sem;

static void
sem_test_thread_proc (void *args) {
  fm_sem_post(&s_sem);
  fm_sem_post(&s_sem);
  fm_sem_post(&s_sem);
}

UNIT_TEST(sem) {
  fm_thread_t t;

  fm_sem_init(&s_sem, 0);

  assert_int_equal(fm_thread_create(&t, sem_test_thread_proc, NULL, 0), 0);

  fm_sem_wait(&s_sem);
  fm_sem_wait(&s_sem);
  fm_sem_wait(&s_sem);
  assert_int_equal(fm_sem_trywait(&s_sem), EAGAIN);

  assert_int_equal(fm_thread_join(&t), 0);

  fm_sem_destroy(&s_sem);
}