/*-
 * Copyright 2002 Niels Provos <provos@citi.umich.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef  FM_MAP_H_
#define  FM_MAP_H_

#ifndef FM__UNUSED
# if __GNUC__
#  define FM__UNUSED __attribute__((unused))
# else
#  define FM__UNUSED
# endif
#endif

#define FM_RB_BLACK  0
#define FM_RB_RED    1

#define FM_RB_LEFT(elm, field)     (elm)->field.rbe_left
#define FM_RB_RIGHT(elm, field)    (elm)->field.rbe_right
#define FM_RB_PARENT(elm, field)   (elm)->field.rbe_parent
#define FM_RB_COLOR(elm, field)    (elm)->field.rbe_color
#define FM_RB_ROOT(head)           (head)->rbh_root
#define FM_RB_SIZE(head)           (head)->rbh_size
#define FM_RB_EMPTY(head)          (FM_RB_ROOT(head) == NULL)

#define FM_RB_SET(elm, parent, field) do {                                                \
  FM_RB_PARENT(elm, field) = parent;                                                      \
  FM_RB_LEFT(elm, field) = FM_RB_RIGHT(elm, field) = NULL;                                \
  FM_RB_COLOR(elm, field) = FM_RB_RED;                                                    \
} while (/*CONSTCOND*/ 0)

#define FM_RB_SET_BLACKRED(black, red, field) do {                                        \
  FM_RB_COLOR(black, field) = FM_RB_BLACK;                                                \
  FM_RB_COLOR(red, field) = FM_RB_RED;                                                    \
} while (/*CONSTCOND*/ 0)

#ifndef FM_RB_AUGMENT
#define FM_RB_AUGMENT(x)  do {} while (0)
#endif

#define FM_RB_ROTATE_LEFT(head, elm, tmp, field) do {                                     \
  (tmp) = FM_RB_RIGHT(elm, field);                                                        \
  if ((FM_RB_RIGHT(elm, field) = FM_RB_LEFT(tmp, field)) != NULL) {                       \
    FM_RB_PARENT(FM_RB_LEFT(tmp, field), field) = (elm);                                  \
  }                                                                                       \
  FM_RB_AUGMENT(elm);                                                                     \
  if ((FM_RB_PARENT(tmp, field) = FM_RB_PARENT(elm, field)) != NULL) {                    \
    if ((elm) == FM_RB_LEFT(FM_RB_PARENT(elm, field), field))                             \
      FM_RB_LEFT(FM_RB_PARENT(elm, field), field) = (tmp);                                \
    else                                                                                  \
      FM_RB_RIGHT(FM_RB_PARENT(elm, field), field) = (tmp);                               \
  } else                                                                                  \
    (head)->rbh_root = (tmp);                                                             \
  FM_RB_LEFT(tmp, field) = (elm);                                                         \
  FM_RB_PARENT(elm, field) = (tmp);                                                       \
  FM_RB_AUGMENT(tmp);                                                                     \
  if ((FM_RB_PARENT(tmp, field)))                                                         \
    FM_RB_AUGMENT(FM_RB_PARENT(tmp, field));                                              \
} while (/*CONSTCOND*/ 0)

#define FM_RB_ROTATE_RIGHT(head, elm, tmp, field) do {                                    \
  (tmp) = FM_RB_LEFT(elm, field);                                                         \
  if ((FM_RB_LEFT(elm, field) = FM_RB_RIGHT(tmp, field)) != NULL) {                       \
    FM_RB_PARENT(FM_RB_RIGHT(tmp, field), field) = (elm);                                 \
  }                                                                                       \
  FM_RB_AUGMENT(elm);                                                                     \
  if ((FM_RB_PARENT(tmp, field) = FM_RB_PARENT(elm, field)) != NULL) {                    \
    if ((elm) == FM_RB_LEFT(FM_RB_PARENT(elm, field), field))                             \
      FM_RB_LEFT(FM_RB_PARENT(elm, field), field) = (tmp);                                \
    else                                                                                  \
      FM_RB_RIGHT(FM_RB_PARENT(elm, field), field) = (tmp);                               \
  } else                                                                                  \
    (head)->rbh_root = (tmp);                                                             \
  FM_RB_RIGHT(tmp, field) = (elm);                                                        \
  FM_RB_PARENT(elm, field) = (tmp);                                                       \
  FM_RB_AUGMENT(tmp);                                                                     \
  if ((FM_RB_PARENT(tmp, field)))                                                         \
    FM_RB_AUGMENT(FM_RB_PARENT(tmp, field));                                              \
} while (/*CONSTCOND*/ 0)

/* Generates prototypes and inline functions */
#define FM_MAP_PROTOTYPE_INTERNAL(name, type, field, cmp_type, attr)                      \
attr void fm_rb_##name##_INSERT_COLOR(struct name *, struct type *);                      \
attr void fm_rb_##name##_REMOVE_COLOR(struct name *, struct type *, struct type *);       \
attr struct type *fm_rb_##name##_REMOVE(struct name *, struct type *);                    \
attr struct type *fm_rb_##name##_INSERT(struct name *, struct type *);                    \
attr struct type *fm_rb_##name##_FIND(struct name *, cmp_type);                           \
attr struct type *fm_rb_##name##_NFIND(struct name *, cmp_type);                          \
attr struct type *fm_rb_##name##_NEXT(struct type *);                                     \
attr struct type *fm_rb_##name##_PREV(struct type *);                                     \
attr struct type *fm_rb_##name##_MINMAX(struct name *, int);

#define FM_MAP_PROTOTYPE_INTERNAL2(name, type, field, cmp, attr)                          \
attr void fm_rb_##name##_INSERT_COLOR(struct name *, struct type *);                      \
attr void fm_rb_##name##_REMOVE_COLOR(struct name *, struct type *, struct type *);       \
attr struct type *fm_rb_##name##_REMOVE(struct name *, struct type *);                    \
attr struct type *fm_rb_##name##_INSERT2(struct name *, struct type *);                   \
attr struct type *fm_rb_##name##_FIND2(struct name *, struct type *);                     \
attr struct type *fm_rb_##name##_NFIND2(struct name *, struct type *);                    \
attr struct type *fm_rb_##name##_NEXT(struct type *);                                     \
attr struct type *fm_rb_##name##_PREV(struct type *);                                     \
attr struct type *fm_rb_##name##_MINMAX(struct name *, int);

/* Main rb operation.
 * Moves node close to the key of elm to top
 */
#define FM_MAP_GENERATE_INTERNAL(name, type, field, cmp_type, cmp_elm, attr)              \
  FM_MAP_GENERATE_INTERNAL_INSERT_COLOR(name, type, field, attr)                          \
  FM_MAP_GENERATE_INTERNAL_REMOVE_COLOR(name, type, field, attr)                          \
  FM_MAP_GENERATE_INTERNAL_REMOVE(name, type, field, attr)                                \
  FM_MAP_GENERATE_INTERNAL_INSERT(name, type, field, cmp_type, cmp_elm, attr)             \
  FM_MAP_GENERATE_INTERNAL_FIND(name, type, field, cmp_type, cmp_elm, attr)               \
  FM_MAP_GENERATE_INTERNAL_NFIND(name, type, field, cmp_type, cmp_elm, attr)              \
  FM_MAP_GENERATE_INTERNAL_NEXT(name, type, field, attr)                                  \
  FM_MAP_GENERATE_INTERNAL_PREV(name, type, field, attr)                                  \
  FM_MAP_GENERATE_INTERNAL_MINMAX(name, type, field, attr)

#define FM_MAP_GENERATE_INTERNAL2(name, type, field, cmp, attr)                           \
  FM_MAP_GENERATE_INTERNAL_INSERT_COLOR(name, type, field, attr)                          \
  FM_MAP_GENERATE_INTERNAL_REMOVE_COLOR(name, type, field, attr)                          \
  FM_MAP_GENERATE_INTERNAL_REMOVE(name, type, field, attr)                                \
  FM_MAP_GENERATE_INTERNAL_INSERT2(name, type, field, cmp, attr)                          \
  FM_MAP_GENERATE_INTERNAL_FIND2(name, type, field, cmp, attr)                            \
  FM_MAP_GENERATE_INTERNAL_NFIND2(name, type, field, cmp, attr)                           \
  FM_MAP_GENERATE_INTERNAL_NEXT(name, type, field, attr)                                  \
  FM_MAP_GENERATE_INTERNAL_PREV(name, type, field, attr)                                  \
  FM_MAP_GENERATE_INTERNAL_MINMAX(name, type, field, attr)

#define FM_MAP_GENERATE_INTERNAL_INSERT_COLOR(name, type, field, attr)                    \
attr void                                                                                 \
fm_rb_##name##_INSERT_COLOR(struct name *head, struct type *elm)                          \
{                                                                                         \
  struct type *parent, *gparent, *tmp;                                                    \
  while ((parent = FM_RB_PARENT(elm, field)) != NULL &&                                   \
      FM_RB_COLOR(parent, field) == FM_RB_RED) {                                          \
    gparent = FM_RB_PARENT(parent, field);                                                \
    if (parent == FM_RB_LEFT(gparent, field)) {                                           \
      tmp = FM_RB_RIGHT(gparent, field);                                                  \
      if (tmp && FM_RB_COLOR(tmp, field) == FM_RB_RED) {                                  \
        FM_RB_COLOR(tmp, field) = FM_RB_BLACK;                                            \
        FM_RB_SET_BLACKRED(parent, gparent, field);                                       \
        elm = gparent;                                                                    \
        continue;                                                                         \
      }                                                                                   \
      if (FM_RB_RIGHT(parent, field) == elm) {                                            \
        FM_RB_ROTATE_LEFT(head, parent, tmp, field);                                      \
        tmp = parent;                                                                     \
        parent = elm;                                                                     \
        elm = tmp;                                                                        \
      }                                                                                   \
      FM_RB_SET_BLACKRED(parent, gparent, field);                                         \
      FM_RB_ROTATE_RIGHT(head, gparent, tmp, field);                                      \
    } else {                                                                              \
      tmp = FM_RB_LEFT(gparent, field);                                                   \
      if (tmp && FM_RB_COLOR(tmp, field) == FM_RB_RED) {                                  \
        FM_RB_COLOR(tmp, field) = FM_RB_BLACK;                                            \
        FM_RB_SET_BLACKRED(parent, gparent, field);                                       \
        elm = gparent;                                                                    \
        continue;                                                                         \
      }                                                                                   \
      if (FM_RB_LEFT(parent, field) == elm) {                                             \
        FM_RB_ROTATE_RIGHT(head, parent, tmp, field);                                     \
        tmp = parent;                                                                     \
        parent = elm;                                                                     \
        elm = tmp;                                                                        \
      }                                                                                   \
      FM_RB_SET_BLACKRED(parent, gparent, field);                                         \
      FM_RB_ROTATE_LEFT(head, gparent, tmp, field);                                       \
    }                                                                                     \
  }                                                                                       \
  FM_RB_COLOR(head->rbh_root, field) = FM_RB_BLACK;                                       \
}

#define FM_MAP_GENERATE_INTERNAL_REMOVE_COLOR(name, type, field, attr)                    \
attr void                                                                                 \
fm_rb_##name##_REMOVE_COLOR(struct name *head, struct type *parent,                       \
    struct type *elm)                                                                     \
{                                                                                         \
  struct type *tmp;                                                                       \
  while ((elm == NULL || FM_RB_COLOR(elm, field) == FM_RB_BLACK) &&                       \
      elm != FM_RB_ROOT(head)) {                                                          \
    if (FM_RB_LEFT(parent, field) == elm) {                                               \
      tmp = FM_RB_RIGHT(parent, field);                                                   \
      if (FM_RB_COLOR(tmp, field) == FM_RB_RED) {                                         \
        FM_RB_SET_BLACKRED(tmp, parent, field);                                           \
        FM_RB_ROTATE_LEFT(head, parent, tmp, field);                                      \
        tmp = FM_RB_RIGHT(parent, field);                                                 \
      }                                                                                   \
      if ((FM_RB_LEFT(tmp, field) == NULL ||                                              \
          FM_RB_COLOR(FM_RB_LEFT(tmp, field), field) == FM_RB_BLACK) &&                   \
          (FM_RB_RIGHT(tmp, field) == NULL ||                                             \
          FM_RB_COLOR(FM_RB_RIGHT(tmp, field), field) == FM_RB_BLACK)) {                  \
        FM_RB_COLOR(tmp, field) = FM_RB_RED;                                              \
        elm = parent;                                                                     \
        parent = FM_RB_PARENT(elm, field);                                                \
      } else {                                                                            \
        if (FM_RB_RIGHT(tmp, field) == NULL ||                                            \
            FM_RB_COLOR(FM_RB_RIGHT(tmp, field), field) == FM_RB_BLACK) {                 \
          struct type *oleft;                                                             \
          if ((oleft = FM_RB_LEFT(tmp, field))                                            \
              != NULL)                                                                    \
            FM_RB_COLOR(oleft, field) = FM_RB_BLACK;                                      \
          FM_RB_COLOR(tmp, field) = FM_RB_RED;                                            \
          FM_RB_ROTATE_RIGHT(head, tmp, oleft, field);                                    \
          tmp = FM_RB_RIGHT(parent, field);                                               \
        }                                                                                 \
        FM_RB_COLOR(tmp, field) = FM_RB_COLOR(parent, field);                             \
        FM_RB_COLOR(parent, field) = FM_RB_BLACK;                                         \
        if (FM_RB_RIGHT(tmp, field))                                                      \
          FM_RB_COLOR(FM_RB_RIGHT(tmp, field), field) = FM_RB_BLACK;                      \
        FM_RB_ROTATE_LEFT(head, parent, tmp, field);                                      \
        elm = FM_RB_ROOT(head);                                                           \
        break;                                                                            \
      }                                                                                   \
    } else {                                                                              \
      tmp = FM_RB_LEFT(parent, field);                                                    \
      if (FM_RB_COLOR(tmp, field) == FM_RB_RED) {                                         \
        FM_RB_SET_BLACKRED(tmp, parent, field);                                           \
        FM_RB_ROTATE_RIGHT(head, parent, tmp, field);                                     \
        tmp = FM_RB_LEFT(parent, field);                                                  \
      }                                                                                   \
      if ((FM_RB_LEFT(tmp, field) == NULL ||                                              \
          FM_RB_COLOR(FM_RB_LEFT(tmp, field), field) == FM_RB_BLACK) &&                   \
          (FM_RB_RIGHT(tmp, field) == NULL ||                                             \
          FM_RB_COLOR(FM_RB_RIGHT(tmp, field), field) == FM_RB_BLACK)) {                  \
        FM_RB_COLOR(tmp, field) = FM_RB_RED;                                              \
        elm = parent;                                                                     \
        parent = FM_RB_PARENT(elm, field);                                                \
      } else {                                                                            \
        if (FM_RB_LEFT(tmp, field) == NULL ||                                             \
            FM_RB_COLOR(FM_RB_LEFT(tmp, field), field) == FM_RB_BLACK) {                  \
          struct type *oright;                                                            \
          if ((oright = FM_RB_RIGHT(tmp, field))                                          \
              != NULL)                                                                    \
            FM_RB_COLOR(oright, field) = FM_RB_BLACK;                                     \
          FM_RB_COLOR(tmp, field) = FM_RB_RED;                                            \
          FM_RB_ROTATE_LEFT(head, tmp, oright, field);                                    \
          tmp = FM_RB_LEFT(parent, field);                                                \
        }                                                                                 \
        FM_RB_COLOR(tmp, field) = FM_RB_COLOR(parent, field);                             \
        FM_RB_COLOR(parent, field) = FM_RB_BLACK;                                         \
        if (FM_RB_LEFT(tmp, field))                                                       \
          FM_RB_COLOR(FM_RB_LEFT(tmp, field), field) = FM_RB_BLACK;                       \
        FM_RB_ROTATE_RIGHT(head, parent, tmp, field);                                     \
        elm = FM_RB_ROOT(head);                                                           \
        break;                                                                            \
      }                                                                                   \
    }                                                                                     \
  }                                                                                       \
  if (elm)                                                                                \
    FM_RB_COLOR(elm, field) = FM_RB_BLACK;                                                \
}

#define FM_MAP_GENERATE_INTERNAL_REMOVE(name, type, field, attr)                          \
attr struct type *                                                                        \
fm_rb_##name##_REMOVE(struct name *head, struct type *elm)                                \
{                                                                                         \
  struct type *child, *parent, *old = elm;                                                \
  int color;                                                                              \
  if (FM_RB_LEFT(elm, field) == NULL)                                                     \
    child = FM_RB_RIGHT(elm, field);                                                      \
  else if (FM_RB_RIGHT(elm, field) == NULL)                                               \
    child = FM_RB_LEFT(elm, field);                                                       \
  else {                                                                                  \
    struct type *left;                                                                    \
    elm = FM_RB_RIGHT(elm, field);                                                        \
    while ((left = FM_RB_LEFT(elm, field)) != NULL)                                       \
      elm = left;                                                                         \
    child = FM_RB_RIGHT(elm, field);                                                      \
    parent = FM_RB_PARENT(elm, field);                                                    \
    color = FM_RB_COLOR(elm, field);                                                      \
    if (child)                                                                            \
      FM_RB_PARENT(child, field) = parent;                                                \
    if (parent) {                                                                         \
      if (FM_RB_LEFT(parent, field) == elm)                                               \
        FM_RB_LEFT(parent, field) = child;                                                \
      else                                                                                \
        FM_RB_RIGHT(parent, field) = child;                                               \
      FM_RB_AUGMENT(parent);                                                              \
    } else                                                                                \
      FM_RB_ROOT(head) = child;                                                           \
    if (FM_RB_PARENT(elm, field) == old)                                                  \
      parent = elm;                                                                       \
    (elm)->field = (old)->field;                                                          \
    if (FM_RB_PARENT(old, field)) {                                                       \
      if (FM_RB_LEFT(FM_RB_PARENT(old, field), field) == old)                             \
        FM_RB_LEFT(FM_RB_PARENT(old, field), field) = elm;                                \
      else                                                                                \
        FM_RB_RIGHT(FM_RB_PARENT(old, field), field) = elm;                               \
      FM_RB_AUGMENT(FM_RB_PARENT(old, field));                                            \
    } else                                                                                \
      FM_RB_ROOT(head) = elm;                                                             \
    FM_RB_PARENT(FM_RB_LEFT(old, field), field) = elm;                                    \
    if (FM_RB_RIGHT(old, field))                                                          \
      FM_RB_PARENT(FM_RB_RIGHT(old, field), field) = elm;                                 \
    if (parent) {                                                                         \
      left = parent;                                                                      \
      do {                                                                                \
        FM_RB_AUGMENT(left);                                                              \
      } while ((left = FM_RB_PARENT(left, field)) != NULL);                               \
    }                                                                                     \
    goto color;                                                                           \
  }                                                                                       \
  parent = FM_RB_PARENT(elm, field);                                                      \
  color = FM_RB_COLOR(elm, field);                                                        \
  if (child)                                                                              \
    FM_RB_PARENT(child, field) = parent;                                                  \
  if (parent) {                                                                           \
    if (FM_RB_LEFT(parent, field) == elm)                                                 \
      FM_RB_LEFT(parent, field) = child;                                                  \
    else                                                                                  \
      FM_RB_RIGHT(parent, field) = child;                                                 \
    FM_RB_AUGMENT(parent);                                                                \
  } else                                                                                  \
    FM_RB_ROOT(head) = child;                                                             \
color:                                                                                    \
  if (color == FM_RB_BLACK)                                                               \
    fm_rb_##name##_REMOVE_COLOR(head, parent, child);                                     \
  --FM_RB_SIZE(head);                                                                     \
  return (old);                                                                           \
}

/* Inserts a node into the RB tree */
#define FM_MAP_GENERATE_INTERNAL_INSERT(name, type, field, cmp_type, cmp_elm, attr)       \
attr struct type *                                                                        \
fm_rb_##name##_INSERT(struct name *head, struct type *elm)                                \
{                                                                                         \
  struct type *tmp;                                                                       \
  struct type *parent = NULL;                                                             \
  int less = 0;                                                                           \
  tmp = FM_RB_ROOT(head);                                                                 \
  while (tmp) {                                                                           \
    parent = tmp;                                                                         \
    if ((less = elm->cmp_elm < parent->cmp_elm))                                          \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    else if (parent->cmp_elm < elm->cmp_elm)                                              \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  FM_RB_SET(elm, parent, field);                                                          \
  if (parent != NULL) {                                                                   \
    if (less)                                                                             \
      FM_RB_LEFT(parent, field) = elm;                                                    \
    else                                                                                  \
      FM_RB_RIGHT(parent, field) = elm;                                                   \
    FM_RB_AUGMENT(parent);                                                                \
  } else                                                                                  \
    FM_RB_ROOT(head) = elm;                                                               \
  fm_rb_##name##_INSERT_COLOR(head, elm);                                                 \
  ++FM_RB_SIZE(head);                                                                     \
  return (NULL);                                                                          \
}

/* Inserts a node into the RB tree */
#define FM_MAP_GENERATE_INTERNAL_INSERT2(name, type, field, cmp, attr)                    \
attr struct type *                                                                        \
fm_rb_##name##_INSERT(struct name *head, struct type *elm)                                \
{                                                                                         \
  struct type *tmp;                                                                       \
  struct type *parent = NULL;                                                             \
  int comp = 0;                                                                           \
  tmp = FM_RB_ROOT(head);                                                                 \
  while (tmp) {                                                                           \
    parent = tmp;                                                                         \
    comp = (cmp)(elm, parent);                                                            \
    if (comp < 0)                                                                         \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    else if (comp > 0)                                                                    \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  FM_RB_SET(elm, parent, field);                                                          \
  if (parent != NULL) {                                                                   \
    if (comp < 0)                                                                         \
      FM_RB_LEFT(parent, field) = elm;                                                    \
    else                                                                                  \
      FM_RB_RIGHT(parent, field) = elm;                                                   \
    FM_RB_AUGMENT(parent);                                                                \
  } else                                                                                  \
    FM_RB_ROOT(head) = elm;                                                               \
  fm_rb_##name##_INSERT_COLOR(head, elm);                                                 \
  ++FM_RB_SIZE(head);                                                                     \
  return (NULL);                                                                          \
}

/* Finds the node with the same key as elm */
#define FM_MAP_GENERATE_INTERNAL_FIND(name, type, field, cmp_type, cmp_elm, attr)         \
attr struct type *                                                                        \
fm_rb_##name##_FIND(struct name *head, cmp_type elm)                                      \
{                                                                                         \
  struct type *tmp = FM_RB_ROOT(head);                                                    \
  int comp;                                                                               \
  while (tmp) {                                                                           \
    if (elm < tmp->cmp_elm)                                                               \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    else if (tmp->cmp_elm < elm)                                                          \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  return (NULL);                                                                          \
}

/* Finds the node with the same key as elm */
#define FM_MAP_GENERATE_INTERNAL_FIND2(name, type, field, cmp, attr)                      \
attr struct type *                                                                        \
fm_rb_##name##_FIND(struct name *head, struct type *elm)                                  \
{                                                                                         \
  struct type *tmp = FM_RB_ROOT(head);                                                    \
  int comp;                                                                               \
  while (tmp) {                                                                           \
    comp = cmp(elm, tmp);                                                                 \
    if (comp < 0)                                                                         \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    else if (comp > 0)                                                                    \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  return (NULL);                                                                          \
}

/* Finds the first node greater than or equal to the search key */
#define FM_MAP_GENERATE_INTERNAL_NFIND(name, type, field, cmp_type, cmp_elm, attr)        \
attr struct type *                                                                        \
fm_rb_##name##_NFIND(struct name *head, cmp_type elm)                                     \
{                                                                                         \
  struct type *tmp = FM_RB_ROOT(head);                                                    \
  struct type *res = NULL;                                                                \
  int comp;                                                                               \
  while (tmp) {                                                                           \
    if (elm < tmp->cmp_elm) {                                                             \
      res = tmp;                                                                          \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    }                                                                                     \
    else if (comp > 0)                                                                    \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  return (res);                                                                           \
}

/* Finds the first node greater than or equal to the search key */
#define FM_MAP_GENERATE_INTERNAL_NFIND2(name, type, field, cmp, attr)                     \
attr struct type *                                                                        \
fm_rb_##name##_NFIND(struct name *head, struct type *elm)                                 \
{                                                                                         \
  struct type *tmp = FM_RB_ROOT(head);                                                    \
  struct type *res = NULL;                                                                \
  int comp;                                                                               \
  while (tmp) {                                                                           \
    comp = cmp(elm, tmp);                                                                 \
    if (comp < 0) {                                                                       \
      res = tmp;                                                                          \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    }                                                                                     \
    else if (comp > 0)                                                                    \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
    else                                                                                  \
      return (tmp);                                                                       \
  }                                                                                       \
  return (res);                                                                           \
}

/* ARGSUSED */
#define FM_MAP_GENERATE_INTERNAL_NEXT(name, type, field, attr)                            \
attr struct type *                                                                        \
fm_rb_##name##_NEXT(struct type *elm)                                                     \
{                                                                                         \
  if (FM_RB_RIGHT(elm, field)) {                                                          \
    elm = FM_RB_RIGHT(elm, field);                                                        \
    while (FM_RB_LEFT(elm, field))                                                        \
      elm = FM_RB_LEFT(elm, field);                                                       \
  } else {                                                                                \
    if (FM_RB_PARENT(elm, field) &&                                                       \
        (elm == FM_RB_LEFT(FM_RB_PARENT(elm, field), field)))                             \
      elm = FM_RB_PARENT(elm, field);                                                     \
    else {                                                                                \
      while (FM_RB_PARENT(elm, field) &&                                                  \
          (elm == FM_RB_RIGHT(FM_RB_PARENT(elm, field), field)))                          \
        elm = FM_RB_PARENT(elm, field);                                                   \
      elm = FM_RB_PARENT(elm, field);                                                     \
    }                                                                                     \
  }                                                                                       \
  return (elm);                                                                           \
}

/* ARGSUSED */
#define FM_MAP_GENERATE_INTERNAL_PREV(name, type, field, attr)                            \
attr struct type *                                                                        \
fm_rb_##name##_PREV(struct type *elm)                                                     \
{                                                                                         \
  if (FM_RB_LEFT(elm, field)) {                                                           \
    elm = FM_RB_LEFT(elm, field);                                                         \
    while (FM_RB_RIGHT(elm, field))                                                       \
      elm = FM_RB_RIGHT(elm, field);                                                      \
  } else {                                                                                \
    if (FM_RB_PARENT(elm, field) &&                                                       \
        (elm == FM_RB_RIGHT(FM_RB_PARENT(elm, field), field)))                            \
      elm = FM_RB_PARENT(elm, field);                                                     \
    else {                                                                                \
      while (FM_RB_PARENT(elm, field) &&                                                  \
          (elm == FM_RB_LEFT(FM_RB_PARENT(elm, field), field)))                           \
        elm = FM_RB_PARENT(elm, field);                                                   \
      elm = FM_RB_PARENT(elm, field);                                                     \
    }                                                                                     \
  }                                                                                       \
  return (elm);                                                                           \
}

#define FM_MAP_GENERATE_INTERNAL_MINMAX(name, type, field, attr)                          \
attr struct type *                                                                        \
fm_rb_##name##_MINMAX(struct name *head, int val)                                         \
{                                                                                         \
  struct type *tmp = FM_RB_ROOT(head);                                                    \
  struct type *parent = NULL;                                                             \
  while (tmp) {                                                                           \
    parent = tmp;                                                                         \
    if (val < 0)                                                                          \
      tmp = FM_RB_LEFT(tmp, field);                                                       \
    else                                                                                  \
      tmp = FM_RB_RIGHT(tmp, field);                                                      \
  }                                                                                       \
  return (parent);                                                                        \
}

#define FM_RB_NEGINF   -1
#define FM_RB_INF      1

#define FM_MAP_DEFINE(name, type)                                                         \
struct name {                                                                             \
  struct type *rbh_root; /* root of the tree */                                           \
  size_t rbh_size;       /* size of tree */                                               \
}

#define FM_MAP_INITIALIZER()                                                              \
  { NULL, 0 }

#define FM_MAP_INIT(root) do {                                                            \
  (root)->rbh_root = NULL;                                                                \
  (root)->rbh_size = NULL;                                                                \
} while (/*CONSTCOND*/ 0)

#define  FM_MAP_PROTOTYPE(name, type, field, cmp_type)                                    \
  FM_MAP_PROTOTYPE_INTERNAL(name, type, field, cmp_type,)
#define  FM_MAP_PROTOTYPE_STATIC(name, type, field, cmp_type)                             \
  FM_MAP_PROTOTYPE_INTERNAL(name, type, field, cmp_type, FM__UNUSED static)

#define  FM_MAP_PROTOTYPE_CB(name, type, field, cmp)                                      \
  FM_MAP_PROTOTYPE_INTERNAL2(name, type, field, cmp,)
#define  FM_MAP_PROTOTYPE_STATIC_CB(name, type, field, cmp)                               \
  FM_MAP_PROTOTYPE_INTERNAL2(name, type, field, cmp, FM__UNUSED static)

#define  FM_MAP_GENERATE(name, type, field, cmp_type, cmp_elm)                            \
  FM_MAP_GENERATE_INTERNAL(name, type, field, cmp_type, cmp_elm,)
#define  FM_MAP_GENERATE_STATIC(name, type, field, cmp_type, cmp_elm)                     \
  FM_MAP_GENERATE_INTERNAL(name, type, field, cmp_type, cmp_elm, FM__UNUSED static)

#define  FM_MAP_GENERATE_CB(name, type, field, cmp)                                       \
  FM_MAP_GENERATE_INTERNAL2(name, type, field, cmp,)
#define  FM_MAP_GENERATE_STATIC_CB(name, type, field, cmp)                                \
  FM_MAP_GENERATE_INTERNAL2(name, type, field, cmp, FM__UNUSED static)

#define FM_MAP_NODE(type)                                                                 \
struct {                                                                                  \
  struct type *rbe_left;        /* left element */                                        \
  struct type *rbe_right;       /* right element */                                       \
  struct type *rbe_parent;      /* parent element */                                      \
  int rbe_color;                /* node color */                                          \
}

#define FM_MAP_NODE_INIT(node) do {                                                       \
  (node).rbe_left = NULL;                                                                 \
  (node).rbe_right = NULL;                                                                \
  (node).rbe_parent = NULL;                                                               \
  (node).rbe_color = 0;                                                                   \
} while (0)

#define FM_MAP_NODE_INITIALIZER()                                                         \
  { NULL, NULL, NULL, 0 }

#define FM_MAP_INSERT(name, head, node)      fm_rb_##name##_INSERT(head, node)
#define FM_MAP_REMOVE(name, head, node)      fm_rb_##name##_REMOVE(head, node)
#define FM_MAP_FIND(name, head, node)        fm_rb_##name##_FIND(head, node)
#define FM_MAP_NFIND(name, head, node)       fm_rb_##name##_NFIND(head, node)
#define FM_MAP_FIND_DATA(name, head, data)   fm_rb_##name##_FIND_DATA(head, data)
#define FM_MAP_NFIND_DATA(name, head, data)  fm_rb_##name##_NFIND_DATA(head, data)
#define FM_MAP_NEXT(name, head, node)        fm_rb_##name##_NEXT(node)
#define FM_MAP_PREV(name, head, node)        fm_rb_##name##_PREV(node)
#define FM_MAP_MIN(name, head)               fm_rb_##name##_MINMAX(head, FM_RB_NEGINF)
#define FM_MAP_MAX(name, head)               fm_rb_##name##_MINMAX(head, FM_RB_INF)
#define FM_MAP_SIZE(head)                    FM_RB_SIZE(head)
#define FM_MAP_EMPTY(head)                   FM_RB_EMPTY(head)

#define FM_MAP_FOREACH(pos, name, head)                                                  \
  for ((pos) = FM_MAP_MIN(name, head);                                                   \
       (pos) != NULL;                                                                    \
       (pos) = fm_rb_##name##_NEXT(pos))

#define FM_MAP_FOREACH_FROM(pos, name, node)                                             \
  for ((pos) = (node);                                                                   \
      ((pos) != NULL) && ((node) = fm_rb_##name##_NEXT(pos), (pos) != NULL);             \
       (pos) = (node))

#define FM_MAP_FOREACH_SAFE(pos, name, head, tmp)                                        \
  for ((pos) = FM_MAP_MIN(name, head);                                                   \
      ((pos) != NULL) && ((tmp) = fm_rb_##name##_NEXT(pos), (pos) != NULL);              \
       (pos) = (tmp))

#define FM_MAP_FOREACH_REVERSE(pos, name, head)                                          \
  for ((pos) = FM_MAP_MAX(name, head);                                                   \
       (pos) != NULL;                                                                    \
       (pos) = fm_rb_##name##_PREV(pos))

#define FM_MAP_FOREACH_REVERSE_FROM(pos, name, node)                                     \
  for ((pos) = (node);                                                                   \
      ((pos) != NULL) && ((node) = fm_rb_##name##_PREV(pos), (pos) != NULL);             \
       (pos) = (node))

#define FM_MAP_FOREACH_REVERSE_SAFE(pos, name, head, temp)                               \
  for ((pos) = FM_MAP_MAX(name, head);                                                   \
      ((pos) != NULL) && ((temp) = fm_rb_##name##_PREV(pos), (pos) != NULL);             \
       (pos) = (temp))

#endif
