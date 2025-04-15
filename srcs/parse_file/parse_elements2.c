/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 17:02:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_cylinder(t_elem_lst *elements, char **line)
{
	t_cylinder	cy;
	double		height;
	double		diameter;

	if (tab_len(line) != 6)
		return (false);
	cy.type = CYLINDER;
	if (is_vec(line[1]) == false || is_vec(line[2]) == false)
		return (false);
	cy.pos = get_vec(line[1]);
	cy.axis = get_vec(line[2]);
	diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (false);
	cy.diameter = diameter;
	height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (false);
	cy.height = height;
	if (is_color(line[5]) == false)
		return (false);
	cy.color = get_color(line[5]);
	if (!add_cylinder(elements, &cy))
		return (false);
	return (true);
}
