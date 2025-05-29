/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/29 17:26:03 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	add_cylinder(t_elem_lst *elems, char **line, int texture, int normal)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.radius = ft_atof_parse(line[3]) / 2;
	cy.height = ft_atof_parse(line[4]);
	cy.mat.color = get_color(line[5]);
	cy.mat.texture = NULL;
	cy.mat.normal = NULL;
	if (texture)
	{
		cy.mat.texture = add_texture(elems, line[6]);
		if (!cy.mat.texture)
			return (print_err("Invalid texture file in `cylinder`", 0), false);
	}
	if (normal)
	{
		cy.mat.normal = add_normal(elems, line[6 + texture]);
		if (!cy.mat.normal)
			return (print_err("Invalid normal map file in `cylinder`", 0), false);
	}
	if (!add_element(elems, &cy, sizeof(t_cylinder)))
		return (false);
	return (true);
}
