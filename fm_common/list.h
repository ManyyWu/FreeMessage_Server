#ifndef ASYNC_LIST_H
#define ASYNC_LIST_H

#include <fm_common/common.h>

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) \
  do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

/* list */
struct list_head {
  struct list_head *next;
  struct list_head *prev;
};

void
__list_add (struct list_head *add, struct list_head *prev, struct list_head *next) {
  next->prev = add;
  add->next = next;
  add->prev = prev;
  prev->next = add;
}

void
list_add (struct list_head *add, struct list_head *head) {
  __list_add(add, head, head->next);
}

void
list_add_tail (struct list_head *add, struct list_head *head) {
  __list_add(add, head->prev, head);
}

void
__list_del (struct list_head *prev, struct list_head *next) {
  next->prev = prev;
  prev->next = next;
}

void
list_del (struct list_head *entry) {
  __list_del(entry->prev, entry->next);
}

void
list_del_init (struct list_head* entry) {
  __list_del(entry->prev, entry->next);
  INIT_LIST_HEAD(entry);
}

int
list_empty (struct list_head* head) {
  return head->next == head;
}

int
list_entry_is_last (struct list_head* entry, struct list_head* head) {
  return head->prev == entry;
}

int
list_entry_is_first (struct list_head* entry, struct list_head* head) {
  return head->next == entry;
}

void
list_splice (struct list_head* list, struct list_head* head) {
  struct list_head* first = list->next;

  if (first != list) {
    struct list_head *last = list->prev;
    struct list_head *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
  }
}

#define list_entry(ptr, type, member) \
  container_of(ptr, type, member)

#define list_first_entry(head, type, member) \
  ((head) && (head)->next != (head) ? list_entry((head)->next, type, member) : NULL)

#define list_last_entry(head, type, member) \
  ((head) && (head)->prev != (head) ? list_entry((head)->prev, type, member) : NULL)

#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_backwardly(pos, head) \
  for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_safe(pos, pnext, head) \
  for (pos = (head)->next, pnext = pos->next; pos != (head); \
       pos = pnext, pnext = pos->next)

size_t
list_count_entries (struct list_head *head) {
  struct list_head *pos;
  size_t ct = 0;

  list_for_each(pos, head)
    ct++;

  return ct;
}

#endif