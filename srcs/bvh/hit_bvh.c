/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:57:10 by agruet            #+#    #+#             */
/*   Updated: 2025/06/18 17:07:03 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	return (false);
}

bool	valid_node(t_bvh_node *node)
{
	if (node->is_leaf)
		return (node->obj != NULL);
	return (true);
}


/* bool	hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit, size_t index)
{
	bool			did_hit;
	const size_t	left = index * 2 + 1;
	const size_t	right = index * 2 + 2;

	did_hit = false;
	if (valid_node(&bvh[left]) && hit_aabb(&bvh[left].bbox, r))
	{
		if (bvh[left].is_leaf)
			did_hit |= hit_object(bvh[left].obj, r, hit);
		else
			did_hit |= hit_bvh(bvh, r, hit, left);
	}
	if (valid_node(&bvh[right]) && hit_aabb(&bvh[right].bbox, r))
	{
		if (bvh[right].is_leaf)
			did_hit |= hit_object(bvh[right].obj, r, hit);
		else
			did_hit |= hit_bvh(bvh, r, hit, right);
	}
	return (did_hit);
} */

bool	hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit)
{
	bool	did_hit;
	size_t	index;

	if (bvh[0].is_leaf == true)
		return (hit_object(bvh[0].obj, r, hit));
	else if (!hit_aabb(&bvh[0].bbox, r))
		return (false);
	did_hit = false;
	index = 1;
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
				index = index * 2 + 1;
		}
		else
			index = bvh[index].next;
	}
	return (did_hit);
}
