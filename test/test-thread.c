#include "run_test.h"
#include "fm_kernel/include/thread.h"

static fm_barrier_t s_barrier;

static void
thread_proc (void *args) {
  assert_true(args);
  *(fm_thread_t *)args = fm_thread_self();
  fm_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(thread) {
  fm_thread_t t;
  fm_thread_t t1;

  assert_int_equal(fm_thread_create(&t, NULL, NULL, 0), EINVAL);
  assert_int_equal(fm_thread_create(&t, NULL, &t1, 0), EINVAL);

  fm_barrier_init(&s_barrier, 2);
  assert_int_equal(fm_thread_create(&t, thread_proc, &t1, 0), 0);
  fm_barrier_wait_and_destroy(&s_barrier);
  assert_int_not_equal(fm_thread_equal(&t, &t1), 0);
  assert_int_equal(fm_thread_join(&t), 0);
  assert_int_equal(fm_thread_join(&t), ESRCH);

  fm_barrier_init(&s_barrier, 2);
  assert_int_equal(fm_thread_create(&t, thread_proc, &t1, 409600), 0);
  fm_barrier_wait_and_destroy(&s_barrier);
  assert_int_not_equal(fm_thread_equal(&t, &t1), 0);
  assert_int_equal(fm_thread_join(&t), 0);
  assert_int_equal(fm_thread_join(&t), ESRCH);
}

static void
trace_callback (char *frame) {
  assert_true(frame);
  print_message2(frame);
}

UNIT_TEST(stack_trace) {
  assert_true(fm_stack_trace(trace_callback) > 0);
}

UNIT_TEST(sleep) {
  fm_ns_t begin;
  fm_ms_t diff;
  int i;

  for (i = 0; i < 100; ++i) {
    begin = fm_monotonic_time(0);
    fm_sleep(1);
    diff = (fm_monotonic_time(0) - begin) / FM_USEC;
    assert_true(diff >= 1);
  }
}