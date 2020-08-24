#include "run_test.h"
#include "fm_common/time.h"

#include <inttypes.h>

UNIT_TEST(get_time) {
  print_message2("monotonic time: %" PRIu64 "ns", fm_monotonic_time(0));
  print_message2("monotonic time: %" PRIu64 "ns", fm_monotonic_time(1));
  print_message2("system    time: %" PRIu64 "us", fm_system_time());
}
