#include "ft_strace.h"

size_t	compute_ret_len(int n, unsigned int start, int s_len)
{
	if (n + start > (size_t)s_len)
		return (s_len - start);
	if ((size_t)s_len < start)
		return (0);
	return (n);
}

char	*substr(char const *s, unsigned int start, size_t n)
{
	int		ret_len = compute_ret_len(n, start, strlen(s));

	char*	ret_str = (char *)malloc((ret_len + 1) * sizeof(char));
	if (!ret_str)
		return (NULL);

	strncpy(ret_str, &s[start], ret_len + 1);
	return (ret_str);
}
