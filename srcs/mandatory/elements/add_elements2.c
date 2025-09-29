/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/09/29 18:08:23 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

bool	add_cylinder(t_elem_lst *elems, char **line)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.r = ft_atof_parse(line[3]) / 2;
	cy.h = ft_atof_parse(line[4]);
	cy.color = get_color(line[5]);
	return (add_element(elems, &cy, sizeof(t_cylinder)) != NULL);
}
