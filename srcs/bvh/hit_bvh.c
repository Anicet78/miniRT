/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:57:10 by agruet            #+#    #+#             */
/*   Updated: 2025/09/24 16:09:02 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

bool	hit_object(void *obj, t_ray *r, t_hit *hit)
{
	uint8_t	type;

	if (!obj)
		return (false);
	type = get_elem_type(obj);
	if (type == SPHERE)
		return (hit_sphere(obj, r, hit));
	if (type == CYLINDER)
		return (hit_cylinder(obj, r, hit));
	if (type == CONE)
		return (hit_cone(obj, r, hit));
	return (false);
}

bool	valid_node(t_bvh_node *node)
{
	if (node->is_leaf)
		return (node->obj != NULL);
	return (true);
}

bool	hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit)
{
	bool	did_hit;
	size_t	index;

	if (bvh[0].is_leaf == true)
		return (hit_aabb(&bvh[0].bbox, r) && hit_object(bvh[0].obj, r, hit));
	else if (!hit_aabb(&bvh[0].bbox, r))
		return (false);
	did_hit = false;
	index = bvh[0].left;
	while (index != 0 && valid_node(&bvh[index]))
	{
		if (hit_aabb(&bvh[index].bbox, r))
		{
			if (bvh[index].is_leaf)
			{
				did_hit |= hit_object(bvh[index].obj, r, hit);
				index = bvh[index].next;
			}
			else
				index = bvh[index].left;
		}
		else
			index = bvh[index].next;
	}
	return (did_hit);
}

bool	shadow_hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit)
{
	size_t	index;

	if (bvh[0].is_leaf == true)
		return (hit_aabb(&bvh[0].bbox, r) && hit_object(bvh[0].obj, r, hit));
	else if (!hit_aabb(&bvh[0].bbox, r))
		return (false);
	index = 1;
	while (index != 0 && valid_node(&bvh[index]))
	{
		if (hit_aabb(&bvh[index].bbox, r))
		{
			if (bvh[index].is_leaf)
			{
				if (hit_object(bvh[index].obj, r, hit))
					return (true);
				index = bvh[index].next;
			}
			else
				index = bvh[index].left;
		}
		else
			index = bvh[index].next;
	}
	return (false);
}
