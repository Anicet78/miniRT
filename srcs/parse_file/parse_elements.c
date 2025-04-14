/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/04/14 17:06:28 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_ambient(t_elem_lst *elements, char **line)
{
	float		ratio;
	uint32_t	color;

	if (tab_len(line) != 3)
		return (false);
	ratio = ft_atof(line[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	if (is_color(line[2]) == false)
		return (false);
	color = get_color(line[2]);
	add_ambient_lighting(elements, ratio, color);
	return (true);
}

bool	parse_camera(t_elem_lst *elements, char **line)
{
	t_point	point;

	if (tab_len(line) != 4)
		return (false);
	if (is_pos(line[1]) == false)
		return (false);
	point = get_pos(line[1]);
	ft_printf("%d,%d,%d\n", point.x, point.y, point.z);
	return (true);
}

bool	parse_light(t_elem_lst *elements, char **line)
{
	if (tab_len(line) != 3)
		return (false);
	return (true);
}

bool	parse_plane(t_elem_lst *elements, char **line)
{
	if (tab_len(line) != 3)
		return (false);
	return (true);
}

bool	parse_sphere(t_elem_lst *elements, char **line)
{
	if (tab_len(line) != 3)
		return (false);
	return (true);
}
