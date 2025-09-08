/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_parse_elements2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 13:35:06 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

bool	parse_cylinder(t_elem_lst *elems, char **line, int nb)
{
	double	height;
	double	diameter;

	if (tab_len(line) != 6)
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	if (is_vec(line[1]) == false || is_normalize_vec(line[2]) == false)
		return (print_err("Invalid vector in `cylinder`", nb));
	diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `cylinder`", nb));
	height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (print_err("Invalid height in `cylinder`", nb));
	if (is_color(line[5]) == false)
		return (print_err("Invalid color in `cylinder`", nb));
	return (mand_add_cylinder(elems, line));
}
