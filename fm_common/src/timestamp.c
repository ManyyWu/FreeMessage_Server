#include "timestamp.h"

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#ifdef FM_SYSTEM_LINUX
#include <execinfo.h>
#endif

#define STACK_TRACE_LINE 128

fm_ns_t
fm_monotonic_time (int fast) {
  static int fast_clock_id = -1;
  struct timespec ts;

  if (fast_clock_id == -1 && fast) {
#if defined(CLOCK_MONOTONIC_COARSE)
    if (!clock_getres(CLOCK_MONOTONIC_COARSE, &ts) && ts.tv_nsec <= 1e6)
      fast_clock_id = CLOCK_MONOTONIC_COARSE;
    else
#endif
    fast_clock_id = CLOCK_MONOTONIC;
  }
  if (clock_gettime((fast ? fast_clock_id : CLOCK_MONOTONIC), &ts))
    abort();
  return FM_TIMESPEC_TO_NS(ts);
}

fm_us_t
fm_system_time () {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    abort();

  return FM_TIMEVAL_TO_US(tv);
}

int
fm_stack_trace (void (*callback) (char*)) {
#ifdef FM_SYSTEM_LINUX
  void *array[STACK_TRACE_LINE];
  char **stacks;
  int line;
  int i;

  if (!callback)
    return EINVAL;

  line = backtrace(array, STACK_TRACE_LINE);
  if (line <= 0)
    return ENOMEM;

  stacks = backtrace_symbols(array, line);
  if (!stacks)
    return ENOMEM;

  for (i = 0; i < line; ++i)
    callback(stacks[i]);

  free(stacks);

  return line;
#endif
}
