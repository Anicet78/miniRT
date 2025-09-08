/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:11:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

bool	add_cylinder(t_elem_lst *elems, char **line)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.pos = get_vec(line[1]);
	cy.axis = norm(get_vec(line[2]));
	cy.radius = ft_atof_parse(line[3]) / 2;
	cy.height = ft_atof_parse(line[4]);
	cy.color = get_color(line[5]);
	return (add_element(elems, &cy, sizeof(t_cylinder)) != NULL);
}
