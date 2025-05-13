/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 04:51:51 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_cylinder(t_elem_lst *elements, char **line, int nb)
{
	t_cylinder	cy;
	double		height;
	double		diameter;

	if (tab_len(line) != 6)
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	cy.type = CYLINDER;
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `cylinder`", nb));
	if (is_normalize_vec(line[2]) == false)
		return (print_err("Invalid axis vector in `cylinder`", nb));
	cy.pos = get_vec(line[1]);
	cy.axis = get_vec(line[2]);
	diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `cylinder`", nb));
	cy.radius = diameter / 2;
	height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (print_err("Invalid height in `cylinder`", nb));
	cy.height = height;
	if (is_color(line[5]) == false)
		return (print_err("Invalid color in `cylinder`", nb));
	cy.mat.color = get_color(line[5]);
	return (add_cylinder(elements, &cy));
}
