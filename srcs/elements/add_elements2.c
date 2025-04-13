/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 21:08:09 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder	*add_cylinder(t_elem_lst *elements, t_point pos, t_vec axis,
	float diameter, float height, uint32_t color)
{
	t_cylinder	cy;

	cy.type = CYLINDER;
	cy.color = color;
	cy.pos = pos;
	cy.axis = axis;
	cy.diameter = diameter;
	cy.height = height;
	if (!add_element(elements, &cy, sizeof(t_cylinder)))
		return (NULL);
	return ((t_cylinder *)1);
}
