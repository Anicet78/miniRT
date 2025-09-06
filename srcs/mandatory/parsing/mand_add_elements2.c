/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_add_elements2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 19:29:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

bool	mand_add_cylinder(t_mandlst *elems, char **line)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.radius = ft_atof_parse(line[3]) / 2;
	cy.height = ft_atof_parse(line[4]);
	cy.mat.color = get_color(line[5]);
	return (mand_add_element(elems, &cy, sizeof(t_cylinder)) != NULL);
}
