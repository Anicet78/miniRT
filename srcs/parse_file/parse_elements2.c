/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/04/14 17:11:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_cylinder(t_elem_lst *elements, char **line)
{
	if (tab_len(line) != 3)
		return (false);
	return (true);
}

bool	is_color(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = ft_atoi(str);
	while (ft_isdigit(str[i]) && i < 3)
		i++;
	if (str[i] != ',' || nb < 0 || nb > 255)
		return (false);
	i++;
	nb = ft_atoi(str + i);
	while (ft_isdigit(str[i]) && i < 7)
		i++;
	if (str[i] != ',' || nb < 0 || nb > 255)
		return (false);
	i++;
	nb = ft_atoi(str + i);
	while (ft_isdigit(str[i]) && i < 11)
		i++;
	if (!str[i] || nb < 0 || nb > 255)
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

bool	is_pos(char *str)
{
	int		i;
	double	nb;

	i = 0;
	nb = ft_atof(str);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || nb < INT_MIN || nb > INT_MAX)
		return (false);
	i++;
	nb = ft_atof(str + i);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || nb < INT_MIN || nb > INT_MAX)
		return (false);
	i++;
	nb = ft_atof(str + i);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || nb < INT_MIN || nb > INT_MAX)
		return (false);
	return (true);
}

t_point	get_pos(char *str)
{
	t_point		point;
	int			i;

	i = 0;
	point.x = ft_atof(str);
	while (ft_isdigit(str[i]))
		i++;
	i++;
	point.y = ft_atof(str + i);
	while (ft_isdigit(str[i]))
		i++;
	i++;
	point.z = ft_atof(str + i);
	while (ft_isdigit(str[i]))
		i++;
	return (point);
}
