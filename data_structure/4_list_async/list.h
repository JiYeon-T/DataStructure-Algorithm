#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


// double circle linklist


/**
 * INCLUDE FILES
 */
//#include <nuttx/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Pre-processor definitions
 */

/**
 * cast a member of a struct out to get the address of the containg structure
 *
 * @ptr the pointer to the member
 * @type the type of the container struct this is embedded in
 * @member the name of the member(param @ptr) within the struct
 */
#define container_of(ptr, type, member) \
        ((type*)((uintptr_t)(ptr) - offsetof(type, member)))

//#define container_of(ptr, type, member) \
//{ \
//    (type *)( (char *)ptr - ((size_t)&((type  *)0)->member )); \
//}


#define LIST_INITIAL_VALUE(list)        {&(list), &(list)}
#define LIST_INITIAL_CREATED_VALUE      {NULL, NULL}

#define list_in_list(item)              ((item)->prev) != NULL)
#define list_is_empty(list)             ((list)->next == list) // double circle linklist
#define list_is_clear(list)             ((list)->next == NULL)

#define list_initialize(list) \
    do \
    { \
        struct list_node *__list = (list); \
        __list->prev = __list->next = __list; \
    } \
    while(0)

#define list_clean_node(item) \
    do \
    { \
        struct list_node * __item = (item); \
        __item->prev = __item->next = NULL; \
    } \
    while(0)

#define list_peek_head(list) ((list)->next != (list) ? (list)->next : NULL)
#define list_peek_tail(list) ((list)->prev != (list) ? (list)->prev : NULL)

#define list_prev(list, item) ((item)->prev != (list) ? (item)->prev : NULL)
#define list_prev_wrap(list, item) \
    ((item)->prev != (list) ? (item)->prev : \
     (item)->prev->prev != (list) ? (item)->prev->prev : NULL \
    )

#define list_next(list, item) ((item)->next != (list) ? (item)->next : NULL)
#define list_next_wrap(list, item) \
    ((item)->next != (list) ? (item)->next : \
     (item)->next->next != (list) ? (item)->next->next : NULL \
    )

/**
 * list_entry - get the struct for this entry
 * @ptr the &struct list_head pointer
 * @type the type of the struct this is embeded in
 * @member the name of the list_head within the struct
 */
#define list_entry(ptr, type, member) \
            container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @list the list head to take the element from
 * @type the type of the struct this is embeded in
 * @member the name of the list_head iwthin the struct
 *
 * Note, tha list is expected to be not empty
 */
#define list_first_entry(list, type, member) \
            list_entry((list)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @list the list head to take the element from
 * @type the type of the struct this is embeded in
 * @member the name of the list_head iwthin the struct
 *
 * Note, tha list is expected to be not empty
 */
#define list_last_entry(list, type, member) \
            list_entry((list)->prev, type, member)

#define list_add_after(entry, new_entry) list_add_head(entry, new_entry)
#define list_add_head(list, item) \
    do \
    { \
        struct list_node *__list = (list); \
        struct list_node *__item = (item); \
        __item->next        = __list->next; \
        __item->prev        = __list; \
        __list->next->prev  = __item; \
        __list->next        = __item; \
    } \
    while(0)

#define list_add_before(entry, new_entry) list_add_tail(entry, new_entry)
#define list_add_tail(list, item) \
    do \
    { \
        struct list_node *__list = (list); \
        struct list_node *__item = (item); \
        __item->prev = __list->prev; \
        __item->next = __list; \
        __list->prev->next = __item; \
        __list->prev = __item; \
    } \
    while(0)

#define list_delete(item) \
    do \
    { \
        struct list_node * __item = (item); \
        __item->next->prev = __item->prev; \
        __item->prev->next = __item->next; \
        __item->prev = __item->next = NULL; \
    } \
    while(0)

#define list_remove_head_type(list, type, member) \
    ({ \
        struct list_node *__node = list_remove_head(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_remove_tail_type(list, type, member) \
    ({ \
        struct list_node *__node = list_remove_tail(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_peek_head_type(list, type, member) \
    ({ \
        struct list_node *__node = list_peek_head(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_peek_tail_type(list, type, member) \
    ({ \
        struct list_node *__node = list_peek_tail(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_prev_type(list, type, member) \
    ({ \
        struct list_node *__node = list_prev(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_prev_wrap_type(list, type, member) \
    ({ \
        struct list_node *__node = list_prev_wrap(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_next_type(list, type, member) \
    ({ \
        struct list_node *__node = list_next(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

#define list_next_wrap_type(list, type, member) \
    ({ \
        struct list_node *__node = list_next_wrap(list); \
        type *__t = NULL; \
        if (__node) \
        { \
            __t = container_of(__node, type, member); \
        } \
        __t; \
    })

/**
 * iterates over the list
 * @node should be struct list_node*
 */
#define list_for_every(list, node) \
    for (node = (list)->next; node != (list); node = node->next)

/**
 * iterates over the list in a safe way for deletion of current node
 * @node should be struct list_node*
 * @temp should be struct list_node*
 */
#define list_for_every_safe(list, node, temp) \
    for(node = (list)->next, temp = node->next; \
        node != (list); \
        node = temp, temp = node->next)

/**
 * iterates over the list
 * @entry should be container structure type*
 */
#define list_for_every_entry(list, entry, type, member) \
    for (entry = container_of((list)->next, type, member); \
         &entry->member != (list); \
         entry = container_of(entry->member.next, type, member))

/**
 * iterates over the list in a safe way for deletion of current node
 * @entry should be container structure type*
 * @temp should be container structure type*
 */
#define list_for_every_entry_safe(list, entry, temp, type, member) \
    for (entry = container_of((list)->next, type, member), \
         temp = container_of(entry->member.next, type, member); \
         &entry->member != (list); \
         entry = temp, temp = container_of(entry->member.next, type, member))

/**
 * PUBLIC TYPE DEFINITIONS
 */
struct list_node {
    struct list_node *prev;
    struct list_node *next;
};

/**
 * INLINE FUNCTIONS
 */
static inline struct list_node *list_remove_head(struct list_node *list)
{
    if (list->next != list) {
        struct list_node *item = list->next;
        list_delete(item);
        return item;
    } else {
        return NULL;
    }
}

static inline struct list_node *list_remove_tail(struct list_node *list)
{
    if (list->prev != list) {
        struct list_node *item = list->prev;
        list_delete(item);
        return item;
    } else {
        return NULL;
    }
}

static inline size_t list_length(struct list_node *list)
{
    struct list_node *node = list;
    size_t cnt = 0;

    list_for_every(list, node)
    {
        cnt++;
    }

    return cnt;
}


#endif // LIST_H_INCLUDED
