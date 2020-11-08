#ifndef FM_LIST_H
#define FM_LIST_H

#include <fm_common/include/common.h>

#define FM_LIST_HEAD_INIT(name) { &(name), &(name) }

#define FM_LIST_HEAD(name) fm_list_head_t name = FM_LIST_HEAD_INIT(name)

#define FM_INIT_LIST_HEAD(ptr) \
  do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

/* list */
typedef struct fm_list_head_s {
  struct fm_list_head_s *next;
  struct fm_list_head_s *prev;
} fm_list_head_t;

static inline void
fm__list_add (fm_list_head_t *add, fm_list_head_t *prev, fm_list_head_t *next) {
  next->prev = add;
  add->next = next;
  add->prev = prev;
  prev->next = add;
}

static inline void
fm_list_add (fm_list_head_t *add, fm_list_head_t *head) {
  fm__list_add(add, head, head->next);
}

static inline void
fm_list_add_tail (fm_list_head_t *add, fm_list_head_t *head) {
  fm__list_add(add, head->prev, head);
}

static inline void
fm__list_del (fm_list_head_t *prev, fm_list_head_t *next) {
  next->prev = prev;
  prev->next = next;
}

static inline void
fm_list_del (fm_list_head_t *entry) {
  fm__list_del(entry->prev, entry->next);
}

static inline void
fm_list_del_init (fm_list_head_t* entry) {
  fm__list_del(entry->prev, entry->next);
  FM_INIT_LIST_HEAD(entry);
}

static inline int
fm_list_empty (fm_list_head_t* head) {
  return head->next == head;
}

static inline int
fm_list_entry_is_last (fm_list_head_t* entry, fm_list_head_t* head) {
  return head->prev == entry;
}

static inline int
fm_list_entry_is_first (fm_list_head_t* entry, fm_list_head_t* head) {
  return head->next == entry;
}

static inline void
fm_list_splice (fm_list_head_t* list, fm_list_head_t* head) {
  fm_list_head_t* first = list->next;

  if (first != list) {
    fm_list_head_t *last = list->prev;
    fm_list_head_t *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
  }
}

#define fm_list_entry(ptr, type, member) \
  container_of(ptr, type, member)

#define fm_list_first_entry(head, type, member) \
  ((head) && (head)->next != (head) ? fm_list_entry((head)->next, type, member) : NULL)

#define fm_list_last_entry(head, type, member) \
  ((head) && (head)->prev != (head) ? fm_list_entry((head)->prev, type, member) : NULL)

#define fm_list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)

#define fm_list_for_each_backwardly(pos, head) \
  for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define fm_list_for_each_safe(pos, pnext, head) \
  for (pos = (head)->next, pnext = pos->next; pos != (head); \
       pos = pnext, pnext = pos->next)

static inline size_t
fm_list_count_entries (fm_list_head_t *head) {
  fm_list_head_t *pos;
  size_t ct = 0;

  fm_list_for_each(pos, head)
    ct++;

  return ct;
}

#endif