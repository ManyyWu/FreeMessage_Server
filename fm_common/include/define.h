#ifndef FM_DEFINE_H
#define FM_DEFINE_H

#include <sys/types.h>
#include <stdint.h>
#include <errno.h>

#if defined(__linux__)
# define FM_SYSTEM_LINUX
#elif defined(__unix__)
# define FM_SYSTEM_UNIX
#elif defined(__APPLE__) && defined(__MACH__)
# define FM_SYSTEM_DARWIN
#elif defined(WIN32)
# define FM_SYSTEM_WIN
#else
# error unsupported platform
#endif

#if __GNUC__ >= 4
# define FM_EXPORT __attribute__((visibility("default")))
#else
# define FM_EXPORT
#endif

#endif
