#ifndef __RTK_Common_list_H__
#define __RTK_Common_list_H__

#define INLINE __inline

struct rtk_list_head
{
	struct	rtk_list_head *next, *prev;
};

#define RTK_LIST_HEAD_INIT(name) { &(name), &(name)}

#define RTK_LIST_HEAD(name)	\
	struct rtk_list_head name = RTK_LIST_HEAD_INIT (name)

#define RTK_INIT_LIST_HEAD(ptr)				\
do	{										\
	(ptr)->next = (ptr); (ptr)->prev = ptr;	\
} while(0)

static INLINE void __rtk_list_add(struct rtk_list_head *new, 
		struct rtk_list_head *prev, struct rtk_list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static INLINE void rtk_list_add(struct rtk_list_head *new, struct rtk_list_head *head)
{
	__rtk_list_add(new, head, head->next);
}

static INLINE void rtk_list_add_tail(struct rtk_list_head *new, struct rtk_list_head *head)
{
	__rtk_list_add(new, head->prev, head);
}

static INLINE void __rtk_list_del(struct rtk_list_head *prev, struct rtk_list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static INLINE void rtk_list_del(struct rtk_list_head *entry)
{
	__rtk_list_del(entry->prev, entry->next);
}

static INLINE void rtk_list_del_init(struct rtk_list_head *entry)
{
	__rtk_list_del(entry->prev, entry->next);
	RTK_INIT_LIST_HEAD(entry);
}

static INLINE int rtk_list_empty(struct rtk_list_head *head)
{
	return head->next == head;
}

static INLINE void rtk_list_splice(struct rtk_list_head *list, 
		struct rtk_list_head *head)
{
	struct rtk_list_head *first = list->next;

	if(first != list)
	{
		struct rtk_list_head *last = list->prev;
		struct rtk_list_head *at = head->next;

		first->prev = head;
		head->next = first;

		last->next = at;
		at->prev = last;
	}
}

#define RTK_LIST_ENTRY(ptr, type, member)		\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define RTK_LIST_FOR_EACH(pos, head)			\
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define RTK_LIST_FOR_EACH_SAFE(pos, n, head)	\
	for(pos = (head)->next, n = pos->next; pos!= (head);	\
		pos = n, n = pos->next)

#define RTK_LIST_FOR_EACH_PREV(pos, head)		\
	for(pos = (head)->prev;pos != (head); pos = pos->prev)

#endif
