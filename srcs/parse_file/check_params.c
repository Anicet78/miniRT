/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:38:39 by agruet            #+#    #+#             */
/*   Updated: 2025/04/29 11:47:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	is_color(char *str)
{
	int		i;
	int		j;
	int64_t	nb;

	i = 0;
	nb = ft_atol(str);
	while (ft_isdigit(str[i]) && i < 3)
		i++;
	if (str[i] != ',' || nb < 0 || nb > 255 || i == 0)
		return (false);
	i++;
	j = i;
	nb = ft_atol(str + i);
	while (ft_isdigit(str[i]) && i - j < 3)
		i++;
	if (str[i] != ',' || nb < 0 || nb > 255 || i - j == 0)
		return (false);
	i++;
	j = i;
	nb = ft_atol(str + i);
	while (ft_isdigit(str[i]) && i < 11)
		i++;
	if (i - j == 0 || nb < 0 || nb > 255 || (str[i] != '\n' && str[i]))
		return (false);
	return (true);
}

uint32_t	get_color(char *str)
{
	int			i;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	i = 0;
	r = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	i++;
	g = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	i++;
	b = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	return (rgb_to_hex(r, g, b));
}

bool	is_vec(char *str)
{
	int		i;
	double	nb;

	i = 0;
	nb = ft_atof_parse(str);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (str[i] != ',' || nb < INT_MIN || nb > INT_MAX)
		return (false);
	i++;
	nb = ft_atof_parse(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (str[i] != ',' || nb < INT_MIN || nb > INT_MAX)
		return (false);
	i++;
	nb = ft_atof_parse(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (nb < INT_MIN || nb > INT_MAX || (str[i] != '\n' && str[i]))
		return (false);
	return (true);
}

bool	is_normalize_vec(char *str)
{
	int		i;
	double	nb;

	i = 0;
	nb = ft_atof_parse(str);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (str[i] != ',' || nb < -1 || nb > 1)
		return (false);
	i++;
	nb = ft_atof_parse(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (str[i] != ',' || nb < -1 || nb > 1)
		return (false);
	i++;
	nb = ft_atof_parse(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	if (nb < -1 || nb > 1 || (str[i] != '\n' && str[i]))
		return (false);
	return (true);
}

t_point	get_vec(char *str)
{
	t_point		point;
	int			i;

	i = 0;
	point.x = ft_atof(str);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	i++;
	point.y = ft_atof(str + i);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	i++;
	point.z = ft_atof(str + i);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '.')
		i++;
	return (point);
}
