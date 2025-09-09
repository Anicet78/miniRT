/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/09/09 18:57:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

bool	add_cylinder(t_elem_lst *elems, char **line, int texture, int bmap)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.radius = ft_atof_parse(line[3]) / 2;
	cy.height = ft_atof_parse(line[4]);
	cy.mat.color = get_color(line[5]);
	cy.mat.texture = NULL;
	cy.mat.bmap = NULL;
	if (texture)
	{
		cy.mat.texture = add_texture(elems, line[6]);
		if (!cy.mat.texture)
			return (print_err("Invalid texture file in `cylinder`", 0), false);
	}
	if (bmap)
	{
		cy.mat.bmap = add_bmap(elems, line[6 + texture]);
		if (!cy.mat.bmap)
			return (print_err("Invalid bmap map file in `cylinder`", 0),
				false);
	}
	return (add_element(elems, &cy, sizeof(t_cylinder)) && true);
}

bool	add_cone(t_elem_lst *elems, char **line, int texture, int bmap)
{
	t_cone	cy;

	cy.type = CONE;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.radius = ft_atof_parse(line[3]) / 2;
	cy.height = ft_atof_parse(line[4]);
	cy.mat.color = get_color(line[5]);
	cy.mat.texture = NULL;
	cy.mat.bmap = NULL;
	if (texture)
	{
		cy.mat.texture = add_texture(elems, line[6]);
		if (!cy.mat.texture)
			return (print_err("Invalid texture file in `cone`", 0), false);
	}
	if (bmap)
	{
		cy.mat.bmap = add_bmap(elems, line[6 + texture]);
		if (!cy.mat.bmap)
			return (print_err("Invalid bmap map file in `cone`", 0),
				false);
	}
	return (add_element(elems, &cy, sizeof(t_cone)) && true);
}

bool	add_anti_aliasing(t_elem_lst *elems, char **line, int nb)
{
	static bool	declared = false;
	int64_t		force;

	if (declared == true)
		return (print_err("Multiple declaration of `anti-aliasing`", nb));
	declared = true;
	if (!line[1])
		return (print_err("Invalid amount of argument in `anti-aliasing`", nb));
	force = ft_atof_parse(line[1]);
	if (force < 0 || force > INT_MAX)
		return (print_err("Invalid force in `anti-aliasing`", nb));
	if (force > 10000)
		return (print_err("Force cannot be higher than 10000 in \
`anti-aliasing`", nb));
	elems->aliasing = force;
	return (true);
}
