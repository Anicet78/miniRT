/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_parse_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 13:32:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

bool	parse_ambient(t_elem_lst *elements, char **line, int nb)
{
	float			ratio;
	t_color			color;
	static bool		declared;

	if (declared)
		return (print_err("Multiple declaration of `ambient light`", nb));
	declared = true;
	if (tab_len(line) != 3)
		return (print_err("Invalid amount of argument in `ambient light`", nb));
	ratio = ft_atof(line[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err("Invalid lighting ratio in `ambient light`", nb));
	if (is_color(line[2]) == false)
		return (print_err("Invalid color in `ambient light`", nb));
	color = get_color(line[2]);
	add_ambient_lighting(elements, ratio, color);
	return (true);
}

bool	parse_camera(t_elem_lst *elements, char **line, int nb)
{
	t_point			pos;
	t_vec			axis;
	int64_t			fov;
	static bool		declared;

	if (declared)
		return (print_err("Multiple declaration of `camera`", nb));
	declared = true;
	if (tab_len(line) != 4)
		return (print_err("Invalid amount of argument in `camera`", nb));
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `camera`", nb));
	if (is_vec(line[2]) == false)
		return (print_err("Invalid orientation vector in `camera`", nb));
	pos = get_vec(line[1]);
	axis = norm(get_vec(line[2]));
	fov = ft_atol(line[3]);
	if (fov < 0 || fov > 180)
		return (print_err("Invalid FOV in `camera`", nb));
	add_camera(elements, pos, axis, fov);
	return (true);
}

bool	parse_light(t_elem_lst *elements, char **line, int nb)
{
	t_point		pos;
	double		ratio;
	t_color		color;
	static bool	declared;

	if (declared)
		return (print_err("Multiple declaration of `light`", nb));
	declared = true;
	if (tab_len(line) != 4)
		return (print_err("Invalid amount of argument in `light`", nb));
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `light`", nb));
	pos = get_vec(line[1]);
	ratio = ft_atof(line[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_err("Invalid brightness ratio in `light`", nb));
	if (is_color(line[3]) == false)
		return (print_err("Invalid color in `light`", nb));
	color = get_color(line[3]);
	add_light(elements, pos, ratio, color);
	return (true);
}

bool	parse_sphere(t_elem_lst *elements, char **line, int nb)
{
	const size_t	tsize = tab_len(line);
	double			diameter;

	if (tsize != 4)
		return (print_err("Invalid amount of argument in `sphere`", nb));
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `sphere`", nb));
	diameter = ft_atof(line[2]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `sphere`", nb));
	if (is_color(line[3]) == false)
		return (print_err("Invalid color in `sphere`", nb));
	return (add_sphere(elements, line));
}

bool	parse_plane(t_elem_lst *elements, char **line, int nb)
{
	if (tab_len(line) != 4)
		return (print_err("Invalid amount of argument in `plane`", nb));
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `plane`", nb));
	if (is_normalize_vec(line[2]) == false)
		return (print_err("Invalid normal vector in `plane`", nb));
	if (is_color(line[3]) == false)
		return (print_err("Invalid color in `plane`", nb));
	return (add_plane(elements, line));
}
