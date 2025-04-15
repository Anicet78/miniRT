/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 16:56:59 by agruet           ###   ########.fr       */
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
	t_point	pos;
	t_vec	axis;
	int64_t	fov;

	if (tab_len(line) != 4)
		return (false);
	if (is_vec(line[1]) == false || is_vec(line[2]) == false)
		return (false);
	pos = get_vec(line[1]);
	axis = get_vec(line[2]);
	fov = ft_atol(line[3]);
	if (fov < 0 || fov > 128)
		return (false);
	if (!add_camera(elements, pos, axis, fov))
		return (false);
	return (true);
}

bool	parse_light(t_elem_lst *elements, char **line)
{
	t_point		pos;
	double		ratio;
	uint32_t	color;

	if (tab_len(line) != 4)
		return (false);
	if (is_vec(line[1]) == false)
		return (false);
	pos = get_vec(line[1]);
	ratio = ft_atof(line[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	if (is_color(line[3]) == false)
		return (false);
	color = get_color(line[3]);
	if (!add_light(elements, pos, ratio, color))
		return (false);
	return (true);
}

bool	parse_sphere(t_elem_lst *elements, char **line)
{
	t_point		pos;
	double		diameter;
	uint32_t	color;

	if (tab_len(line) != 4)
		return (false);
	if (is_vec(line[1]) == false)
		return (false);
	pos = get_vec(line[1]);
	diameter = ft_atof(line[2]);
	if (diameter < 0 || diameter > INT_MAX)
		return (false);
	if (is_color(line[3]) == false)
		return (false);
	color = get_color(line[3]);
	if (!add_sphere(elements, pos, diameter, color))
		return (false);
	return (true);
}

bool	parse_plane(t_elem_lst *elements, char **line)
{
	t_point		pos;
	t_vec		axis;
	uint32_t	color;

	if (tab_len(line) != 4)
		return (false);
	if (is_vec(line[1]) == false || is_vec(line[2]) == false)
		return (false);
	pos = get_vec(line[1]);
	axis = get_vec(line[2]);
	if (is_color(line[3]) == false)
		return (false);
	color = get_color(line[3]);
	if (!add_plane(elements, pos, axis, color))
		return (false);
	return (true);
}
