#ifndef FM_TIME_H
#define FM_TIME_H

#include "define.h"

typedef uint64_t  fm_time_t;
typedef fm_time_t fm_ns_t;
typedef fm_time_t fm_us_t;
typedef fm_time_t fm_ms_t;

#define FM_NSEC (fm_time_t)1e9
#define FM_USEC (fm_time_t)1e6
#define FM_MSEC (fm_time_t)1e3

#define FM_TIMESPEC_TO_NS(ts)                                                         \
  ((ts).tv_sec*FM_NSEC + (ts).tv_nsec)
#define FM_TIMESPEC_TO_US(ts)                                                         \
  ((ts).tv_sec*FM_USEC + (ts).tv_nsec/FM_MSEC)
#define FM_TIMESPEC_TO_MS(ts)                                                         \
  ((ts).tv_sec*FM_MSEC + (ts).tv_nsec/FM_USEC)
#define FM_NS_TO_TIMESPEC(ts, ns)                                                     \
  do { (ts).tv_sec = (ns)/FM_NSEC; (ts).tv_nsec = (ns)%FM_NSEC; } while (0)
#define FM_US_TO_TIMESPEC(ts, us)                                                     \
  do { (ts).tv_sec = (us)/FM_USEC; (ts).tv_nsec = ((us)%FM_USEC)*FM_MSEC; } while (0)
#define FM_MS_TO_TIMESPEC(ts, ms)                                                     \
  do { (ts).tv_sec = (ms)/FM_MSEC; (ts).tv_nsec = ((ms)%FM_MSEC)*FM_USEC; } while (0)
#define FM_TIMEVAL_TO_US(tv)                                                          \
  ((tv).tv_sec*FM_USEC + (tv).tv_usec)
#define FM_TIMEVAL_TO_MS(tv)                                                          \
  ((tv).tv_sec*FM_MSEC + (tv).tv_usec/FM_MSEC)
#define FM_US_TO_TIMEVAL(tv, us)                                                      \
  do { (tv).tv_sec = (us)/FM_USEC; (tv).tv_usec = (us)%FM_USEC; } while (0)
#define FM_MS_TO_TIMEVAL(tv, ms)                                                      \
  do { (tv).tv_sec = (ms)/FM_MSEC; (tv).tv_usec = ((ms)%FM_MSEC)*FM_MSEC; } while (0)

FM_EXPORT fm_ns_t
fm_monotonic_time (int fast);
FM_EXPORT fm_us_t
fm_system_time (void);

#endif
