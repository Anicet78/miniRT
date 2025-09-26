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

static t_aabb	get_cone_aabb(t_cone *cone)
{
	t_aabb			aabb;
	t_vec			ext;
	const t_point	tip = cone->pos;
	const t_point	base = vadd(cone->pos, vmul(cone->axis, cone->height));

	ext.x = cone->radius * sqrtf(1.0f - cone->axis.x * cone->axis.x);
	ext.y = cone->radius * sqrtf(1.0f - cone->axis.y * cone->axis.y);
	ext.z = cone->radius * sqrtf(1.0f - cone->axis.z * cone->axis.z);
	aabb.min.x = fminf(tip.x, base.x - ext.x);
	aabb.max.x = fmaxf(tip.x, base.x + ext.x);
	aabb.min.y = fminf(tip.y, base.y - ext.y);
	aabb.max.y = fmaxf(tip.y, base.y + ext.y);
	aabb.min.z = fminf(tip.z, base.z - ext.z);
	aabb.max.z = fmaxf(tip.z, base.z + ext.z);
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
