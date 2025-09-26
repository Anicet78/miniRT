/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:58:38 by agruet            #+#    #+#             */
/*   Updated: 2025/09/26 18:13:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

t_aabb	union_aabb(t_aabb bbox1, t_aabb bbox2)
{
	return ((t_aabb){
		.min = vmin(bbox1.min, bbox2.min),
		.max = vmax(bbox1.max, bbox2.max)});
}

static t_aabb	get_sphere_aabb(t_sphere *sphere)
{
	const float		radius = sphere->radius;
	const t_point	pos = sphere->pos;

	return ((t_aabb){
		.min = {{pos.x - radius, pos.y - radius, pos.z - radius}},
		.max = {{pos.x + radius, pos.y + radius, pos.z + radius}}});
}

static t_aabb	get_cylinder_aabb(t_cylinder *cyl)
{
	t_aabb			aabb;
	const t_vec		half_axis = vmul(cyl->axis, cyl->height * 0.5f);
	const t_point	base1 = vsub(cyl->pos, half_axis);
	const t_point	base2 = vadd(cyl->pos, half_axis);
	t_vec			ext;

	ext.x = cyl->radius * sqrtf(1.0f - cyl->axis.x * cyl->axis.x);
	ext.y = cyl->radius * sqrtf(1.0f - cyl->axis.y * cyl->axis.y);
	ext.z = cyl->radius * sqrtf(1.0f - cyl->axis.z * cyl->axis.z);
	aabb.min.x = fminf(base1.x, base2.x) - ext.x;
	aabb.max.x = fmaxf(base1.x, base2.x) + ext.x;
	aabb.min.y = fminf(base1.y, base2.y) - ext.y;
	aabb.max.y = fmaxf(base1.y, base2.y) + ext.y;
	aabb.min.z = fminf(base1.z, base2.z) - ext.z;
	aabb.max.z = fmaxf(base1.z, base2.z) + ext.z;
	return (aabb);
}

static t_aabb get_cone_aabb(t_cone *cone)
{
	t_aabb			aabb;
	const t_vec		axis = norm(cone->axis);
	const t_point	base = vadd(cone->pos, vmul(axis, cone->height));
	t_vec			d;

	d.x = cone->radius * sqrtf(1.0f - axis.x * axis.x);
	d.y = cone->radius * sqrtf(1.0f - axis.y * axis.y);
	d.z = cone->radius * sqrtf(1.0f - axis.z * axis.z);
	aabb.min.x = fminf(cone->pos.x, base.x - d.x);
	aabb.max.x = fmaxf(cone->pos.x, base.x + d.x);
	aabb.min.y = fminf(cone->pos.y, base.y - d.y);
	aabb.max.y = fmaxf(cone->pos.y, base.y + d.y);
	aabb.min.z = fminf(cone->pos.z, base.z - d.z);
	aabb.max.z = fmaxf(cone->pos.z, base.z + d.z);
	return (aabb);
}

t_aabb	get_elem_aabb(void *elem)
{
	uint8_t	type;

	type = get_elem_type(elem);
	if (type == SPHERE)
		return (get_sphere_aabb((t_sphere *)elem));
	else if (type == CYLINDER)
		return (get_cylinder_aabb((t_cylinder *)elem));
	else if (type == CONE)
		return (get_cone_aabb((t_cone *)elem));
	return ((t_aabb){{{0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}}});
}
