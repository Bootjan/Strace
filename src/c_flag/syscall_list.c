#include "ft_strace.h"

typedef struct {
	syslist_t*	prev;
	syslist_t*	current;
}	list_items_t;

#define EXIT_NBR_64 60
#define EXIT_GROUP_NBR_64 231

#define EXIT_NBR_32 1
#define EXIT_GROUP_NBR_32 252

static syslist_t*	create_new_element(long syscall_nbr)
{
	syslist_t*	element = malloc(sizeof(syslist_t));
	if (!element)
		return (NULL);

	element->next = NULL;
	element->calls = 1;
	element->errors = 0;
	element->interval = 0;
	element->syscall_nbr = syscall_nbr;

	return (element);
}

static bool	should_not_be_added(strace_t* strace)
{
	if ((strace->flags & _64BIT_PROC) > 0)
		return (strace->syscall_nbr == EXIT_NBR_64 || strace->syscall_nbr == EXIT_GROUP_NBR_64);
	return (strace->syscall_nbr == EXIT_NBR_32 || strace->syscall_nbr == EXIT_GROUP_NBR_32);
}

static int	add_element_to_list(strace_t* strace, list_items_t* list_items)
{
	syslist_t*	element = create_new_element(strace->syscall_nbr);
	if (!element)
		return (-1);

	if (!list_items->prev)
	{
		element->next = strace->syscall_list;
		strace->syscall_list = element;
		return (0);
	}

	list_items->prev->next = element;
	element->next = list_items->current;
	return (0);
}

int	add_syscall_to_list(strace_t* strace)
{
	if (should_not_be_added(strace) == true)
		return (0);

	syslist_t*	current = strace->syscall_list;
	syslist_t*	prev = NULL;

	while (current)
	{
		if (current->syscall_nbr == strace->syscall_nbr)
			return (current->calls++, 0);
		if (strace->syscall_nbr < current->syscall_nbr)
			break;
		prev = current;
		current = current->next;
	}

	list_items_t	list_items = { prev, current };
	return (add_element_to_list(strace, &list_items));
}

void	update_syscall_list(strace_t* strace)
{
	syslist_t*	current = strace->syscall_list;

	while (current && current->syscall_nbr != strace->syscall_nbr)
		current = current->next;

	if (current && strace->return_value < 0 && (strace->flags & _32BIT_PROC) > 0 && strace->syscall_nbr != 37)
		current->errors++;
	if (current && strace->return_value < 0 && (strace->flags & _64BIT_PROC) > 0 && strace->syscall_nbr != 64)
		current->errors++;

	if (current)
		current->interval += strace->interval;
}
