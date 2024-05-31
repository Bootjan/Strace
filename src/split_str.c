#include "ft_strace.h"

static int	count_total_substrs(const char *s, char c)
{
	int		total_substrs = 0;
	bool	on_word = false;

	for (int i = 0; s[i]; i++)
	{
		if (!on_word && s[i] != c)
			total_substrs++;
		on_word = s[i] != c;
	}
	return (total_substrs);
}

static int	update_start(const char *s, char c, int start, int i)
{
	if (s[i] != c && start == -1)
		return (i);
	if (s[i] == c)
		return (-1);
	return (start);
}

static void	free_ret_str(char **ret_str, int total_words)
{
	if (!ret_str)
		return;
	for (int i = 0; i < total_words + 1; i++)
		if (ret_str[i])
			free(ret_str[i]);
	if (ret_str)
		free(ret_str);
}

static char	**compute_array(char **ret_str, const char *s, char c, int total_substrs)
{
	int	i, j, start;
	i = j = start = 0;

	for (; s[i]; i++)
	{
		if (s[i] == c && start >= 0)
		{
			ret_str[j] = substr(s, start, i - start);
			if (!ret_str[j++])
				return (free_ret_str(ret_str, total_substrs), NULL);
		}
		start = update_start(s, c, start, i);
	}
	if (start >= 0)
	{
		ret_str[j] = substr(s, start, i - start);
		if (!ret_str[j])
			return (free_ret_str(ret_str, total_substrs), NULL);
	}
	return (ret_str);
}

char	**split_str(const char *s, char c)
{
	int		total_substrs = count_total_substrs(s, c);

	char**	ret_str = (char **)calloc((total_substrs + 1), sizeof(char *));
	if (!ret_str)
		return (NULL);

	return (compute_array(ret_str, s, c, total_substrs));
}
