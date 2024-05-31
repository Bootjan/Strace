/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:33:43 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/10 22:35:07 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compute_result(const char *str, int i, int pos_neg)
{
	long	result;
	int		max_iter;

	result = 0;
	max_iter = 0;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]) && max_iter++ < 10)
		result = result * 10 + str[i++] - '0';
	if (result > 2147483648 && pos_neg == -1)
		return (-1);
	if (result > 2147483647 && pos_neg == 1)
		return (-1);
	return ((int)result * pos_neg);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		pos_neg;
	int		result;

	i = 0;
	pos_neg = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		i++;
		pos_neg = -1;
	}
	else if (str[i] == '+')
		i++;
	result = compute_result(str, i, pos_neg);
	return (result);
}
