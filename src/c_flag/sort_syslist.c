#include "ft_strace.h"

static syslist_t*	find_highest(syslist_t* list, syslist_t** prev_of_highest)
{
	syslist_t*	highest, *current, *prev;
	highest = prev = list;
	*prev_of_highest = NULL;
	current = list->next;

	while (current)
	{
		if (current->interval > highest->interval)
		{
			*prev_of_highest = prev;
			highest = current;
		}
		prev = current;
		current = current->next;
	}
	return (highest);
}

static syslist_t*	remove_highest(syslist_t* list, syslist_t* next, syslist_t* prev)
{
	if (!prev)
		return (next);
	prev->next = next;
	return (list);
}

static syslist_t*	append_back(syslist_t* list, syslist_t* highest)
{
	highest->next = NULL;
	if (!list)
		return (highest);
	syslist_t*	current = list;
	while (current->next)
		current = current->next;
	current->next = highest;
	return (list);
}

syslist_t*	sort_syscall_list(syslist_t* list)
{
	syslist_t*	sorted_list, *highest, *prev_of_highest;
	sorted_list = NULL;

	while (list)
	{
		highest = find_highest(list, &prev_of_highest);
		list = remove_highest(list, highest->next, prev_of_highest);
		sorted_list = append_back(sorted_list, highest);
	}
	return (sorted_list);
}
