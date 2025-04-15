/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_remaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:29:24 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 16:30:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	set_decimal(char *str, int *i)
{
	double	result;
	double	j;

	if (str[*i] == '.')
		(*i)++;
	else
		return (0.0);
	result = 0.0;
	j = 0.1;
	while (ft_isdigit(str[*i]))
	{
		result = result + (str[*i] - '0') * j;
		j /= 10;
		(*i)++;
		if (j < 0.0000000000000001)
			return ((double)INT_MAX + 1);
	}
	return (result);
}

double	ft_atof_parse(char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	result = 0.0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return ((double)INT_MAX + 1);
	while (ft_isdigit(str[i]) && result <= INT_MAX)
		result = result * 10 + (str[i++] - '0');
	result += set_decimal(str, &i);
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		return ((double)INT_MAX + 1);
	return (result * sign);
}
