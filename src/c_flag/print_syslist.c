#include "ft_strace.h"

typedef struct {
	int		total_calls;
	int		total_errors;
	double	total_interval;
}	totals_t;

static void	compute_list_totals(totals_t* list_totals, syslist_t* list)
{
	syslist_t*	current = list;

	while (current)
	{
		list_totals->total_calls += current->calls;
		list_totals->total_errors += current->errors;
		list_totals->total_interval += current->interval;
		current = current->next;
	}
}

static void	print_overview(void)
{
	fprintf(stderr, "%6s %10s %10s %10s %10s %-20s\n", "% time", "interval", "usecs/call", "calls", "errors", "syscall");
	fprintf(stderr, "%s %s %s %s %s %s\n", MINUS_STRING_6, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_20);
}

static void	print_current_syscall(syslist_t* current, u_int8_t bit_flag, double total_interval)
{
	fprintf(stderr, "%6.2f %10.6f %10i %10i ", current->interval * 100 / total_interval, current->interval, (int)(current->interval * 1000000 / (double)current->calls), current->calls);
	
	if (current->errors > 0)
		fprintf(stderr, "%10i", current->errors);
	else
		fprintf(stderr, "%10c", ' ');
	
	fprintf(stderr, " %-20s\n", get_syscall_name(current->syscall_nbr, bit_flag));
}

static void	print_totals(totals_t* list_totals)
{
	fprintf(stderr, "%s %s %s %s %s %s\n", MINUS_STRING_6, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_10, MINUS_STRING_20);
	
	int	average_usec_call = (int)(list_totals->total_interval * 1000000 / list_totals->total_calls);
	fprintf(stderr, "100,00 %10.6f %10i %10i ", list_totals->total_interval, average_usec_call, list_totals->total_calls);

	if (list_totals->total_errors > 0)
		fprintf(stderr, "%10i", list_totals->total_errors);
	else
		fprintf(stderr, "%10c", ' ');

	fprintf(stderr, " %-20s\n", "total");
}

void	print_syscall_list(strace_t* strace, u_int8_t bit_flag)
{
	totals_t	list_totals = { 0, 0, 0 };
	compute_list_totals(&list_totals, strace->syscall_list);

	syslist_t*	current = sort_syscall_list(strace->syscall_list);
	syslist_t*	next = NULL;

	print_overview();

	while (current)
	{
		print_current_syscall(current, bit_flag, list_totals.total_interval);

		next = current->next;
		free(current);
		current = next;
	}

	print_totals(&list_totals);
}
