#ifndef FM_COMMON_H
#define FM_COMMON_H

#include <stddef.h>

/* offset */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#undef offsetof
#if defined(__compiler_offsetof)
# define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE, MEMBER)
#else
# define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#undef offset
#if defined(__GNUC__)
#define container_of(ptr, type, member) ({               \
  const typeof( ((type *)0)->member ) *__mptr = (ptr);   \
  (type *)( (char *)__mptr - offsetof(type, member) );})
#else
# define container_of(ptr, type, member)                 \
  ((type *) ((char *) (ptr) - offsetof(type, member)))
#endif

/* unique id */
#if defined(__GNUC__)
# define AS_UNIQUE_ID(name) \
  __libasync_internal_##name##__COUNTER__
#else
  __libasync_internal_##name
#endif

/* stderr */
#define STDERR_LOG(fmt, ...) \
  fprintf(stderr, fmt "\n", ##__ARGS__)
#define STDERR_LOG_ERRNO(fmt, ...) \
  fprintf(stderr, fmt ": %s\n", ##__VA_ARGS__, strerror(errno))

#endif
