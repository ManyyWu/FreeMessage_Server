#ifndef FM_THREAD_H
#define FM_THREAD_H

#include "fm_common/include/timestamp.h"

#include <semaphore.h>
#include <pthread.h>

#if defined(FM_SYSTEM_DARWIN)
typedef semaphone_t fm_platform_sem_t;
#else
typedef sem_t fm_platform_sem_t;
#endif

typedef pthread_mutex_t   fm_mutex_t;
typedef pthread_rwlock_t  fm_rwlock_t;
typedef pthread_cond_t    fm_cond_t;
typedef pthread_barrier_t fm_barrier_t;
typedef fm_platform_sem_t fm_sem_t;
typedef pthread_t         fm_thread_t;
typedef pthread_once_t    fm_once_t;

/* mutex */
FM_EXPORT int
fm_mutex_init (fm_mutex_t *mutex);
FM_EXPORT int
fm_recursive_mutex_init (fm_mutex_t *mutex);
FM_EXPORT void
fm_mutex_destroy (fm_mutex_t *mutex);
FM_EXPORT void
fm_mutex_lock (fm_mutex_t *mutex);
FM_EXPORT void
fm_mutex_unlock (fm_mutex_t *mutex);
FM_EXPORT int
fm_mutex_trylock (fm_mutex_t *mutex);

/* rwlock */
FM_EXPORT int
fm_rwlock_init (fm_rwlock_t *rwlock);
FM_EXPORT void
fm_rwlock_destroy (fm_rwlock_t *rwlock);
FM_EXPORT void
fm_rwlock_rdlock (fm_rwlock_t *rwlock);
FM_EXPORT void
fm_rwlock_rdunlock (fm_rwlock_t *rwlock);
FM_EXPORT int
fm_rwlock_rdtrylock (fm_rwlock_t *rwlock);
FM_EXPORT void
fm_rwlock_wrlock (fm_rwlock_t *rwlock);
FM_EXPORT void
fm_rwlock_wrunlock (fm_rwlock_t *rwlock);
FM_EXPORT int
fm_rwlock_wrtrylock (fm_rwlock_t *rwlock);

/* condition variable */
FM_EXPORT int
fm_cond_init (fm_cond_t *cond);
FM_EXPORT void
fm_cond_destroy (fm_cond_t *cond);
FM_EXPORT void
fm_cond_signal (fm_cond_t *cond);
FM_EXPORT void
fm_cond_broadcast (fm_cond_t *cond);
FM_EXPORT void
fm_cond_wait (fm_cond_t *cond, fm_mutex_t *mutex);
FM_EXPORT int
fm_cond_timedwait (fm_cond_t *cond, fm_mutex_t *mutex, fm_ns_t timeout);

/* barrier */
FM_EXPORT int
fm_barrier_init (fm_barrier_t *barrier, uint32_t count);
FM_EXPORT void
fm_barrier_destroy (fm_barrier_t *barrier);
FM_EXPORT void
fm_barrier_wait_and_destroy (fm_barrier_t *barrier);
FM_EXPORT int
fm_barrier_wait (fm_barrier_t *barrier);

/* semaphone */
FM_EXPORT int
fm_sem_init (fm_sem_t *sem, unsigned int value);
FM_EXPORT void
fm_sem_destroy (fm_sem_t *sem);
FM_EXPORT void
fm_sem_post (fm_sem_t* sem);
FM_EXPORT void
fm_sem_wait (fm_sem_t* sem);
FM_EXPORT int
fm_sem_trywait (fm_sem_t* sem);

/* thread */
typedef uint64_t fm_tid_t;
typedef void (*fm_thread_entry) (void *args);

FM_EXPORT int
fm_thread_create (fm_thread_t* t, fm_thread_entry entry, void* args, size_t stack_size);
FM_EXPORT fm_thread_t
fm_thread_self (void);
FM_EXPORT fm_tid_t
fm_thread_tid (void);
FM_EXPORT int
fm_thread_join (const fm_thread_t* t);
FM_EXPORT int
fm_thread_equal (const fm_thread_t* t1, const fm_thread_t* t2);
FM_EXPORT int
fm_stack_trace (void (*callback) (char*));
FM_EXPORT void
fm_sleep (fm_ms_t ms);
FM_EXPORT void
fm_once (fm_once_t* once, void (*callback)(void));

#endif
