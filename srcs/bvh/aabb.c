/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:58:38 by agruet            #+#    #+#             */
/*   Updated: 2025/06/06 15:07:27 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_aabb	get_sphere_aabb(t_sphere *sphere)
{
	const float		radius = sphere->radius;
	const t_point	pos = sphere->pos;

	return ((t_aabb){.min = {pos.x - radius, pos.y - radius, pos.z - radius},
		.max = {pos.x + radius, pos.y + radius, pos.z + radius}});
}

static t_aabb	get_cylinder_aabb(t_cylinder *cylinder)
{
	const t_point	a = cylinder->pos;
	const t_point	b = vadd(a, vmul(cylinder->axis, cylinder->height));
	const t_point	tmp = {cylinder->radius, cylinder->radius,
				cylinder->radius};

	return ((t_aabb){.min = vsub(vmin(a, b), tmp), .max = vadd(vmax(a, b), tmp)});
}

t_aabb	get_elem_aabb(void *elem)
{
	uint8_t	type;
	t_point	*pos;

	type = get_elem_type(elem);
	if (type == SPHERE)
		return (get_sphere_aabb((t_sphere *)&elem));
	else if (type == CYLINDER)
		return (get_cylinder_aabb((t_cylinder *)&elem));
	return ((t_aabb){{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});
}
