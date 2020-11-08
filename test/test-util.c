#include "run_test.h"
#include "fm_common/include/timestamp.h"
#include "fm_kernel/include/thread.h"

UNIT_TEST(version) {
}

UNIT_TEST(macros) {
  struct timespec ts;
  struct timeval tv;

  assert_true(sizeof(FM_TIMESPEC_TO_NS(ts)) == sizeof(uint64_t));
  assert_true(sizeof(FM_TIMESPEC_TO_US(ts)) == sizeof(uint64_t));
  assert_true(sizeof(FM_TIMESPEC_TO_MS(ts)) == sizeof(uint64_t));

  ts.tv_sec = 1;
  ts.tv_nsec = 3000000;
  assert_true(FM_TIMESPEC_TO_NS(ts) == 1003000000);
  assert_true(FM_TIMESPEC_TO_US(ts) == 1003000);
  assert_true(FM_TIMESPEC_TO_MS(ts) == 1003);

  ts.tv_sec = 1;
  ts.tv_nsec = 3000;
  assert_true(FM_TIMESPEC_TO_NS(ts) == 1000003000);
  assert_true(FM_TIMESPEC_TO_US(ts) == 1000003);
  assert_true(FM_TIMESPEC_TO_MS(ts) == 1000);

  FM_NS_TO_TIMESPEC(ts, 1003000000);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 3000000);
  FM_US_TO_TIMESPEC(ts, 1003000);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 3000000);
  FM_MS_TO_TIMESPEC(ts, 1003);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 3000000);

  FM_NS_TO_TIMESPEC(ts, 1000003000);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 3000);
  FM_US_TO_TIMESPEC(ts, 1000003);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 3000);
  FM_MS_TO_TIMESPEC(ts, 1000);
  assert_true(ts.tv_sec == 1 && ts.tv_nsec == 0);

  assert_true(sizeof(FM_TIMEVAL_TO_US(tv)) == sizeof(uint64_t));
  assert_true(sizeof(FM_TIMEVAL_TO_MS(tv)) == sizeof(uint64_t));

  tv.tv_sec = 1;
  tv.tv_usec = 300000;
  assert_true(FM_TIMEVAL_TO_US(tv) == 1300000);
  assert_true(FM_TIMEVAL_TO_MS(tv) == 1300);

  FM_US_TO_TIMEVAL(tv, 1300000);
  assert_true(tv.tv_sec == 1 && tv.tv_usec == 300000);
  FM_MS_TO_TIMEVAL(tv, 1300);
  assert_true(tv.tv_sec == 1 && tv.tv_usec == 300000);
}

static void
once_callback (void) {
  static int i = 0;
  assert_int_equal(i++, 0);
  print_message2("once_callback");
}

UNIT_TEST(once) {
  fm_once_t once;
  fm_once(&once, once_callback);
  fm_once(&once, once_callback);
}