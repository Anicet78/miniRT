/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:15:06 by agruet            #+#    #+#             */
/*   Updated: 2025/07/16 16:42:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

size_t	count_elem_amount(t_elem_lst *elems, size_t frame)
{
	void	*elem;
	size_t	count;

	elems->count = 0;
	if (frame > 0)
		elems->count = elems->frames[frame - 1];
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[frame])
	{
		count++;
		elem = get_next_elem(elems);
	}
	return (count);
}

void	init_builder(t_elem_lst *elems, t_bvh_builder *builder, size_t frame)
{
	void	*elem;
	size_t	count;
	t_aabb	aabb;

	elems->count = 0;
	if (frame > 0)
		elems->count = elems->frames[frame - 1];
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[frame])
	{
		aabb = get_elem_aabb(elem);
		builder[count].bbox = aabb;
		builder[count].obj = elem;
		builder[count].centroid = vmul(vadd(aabb.min, aabb.max), 0.5);
		elem = get_next_elem(elems);
		count++;
	}
}

void	calc_centroid(t_bvh_info *info)
{
	size_t	i;
	t_point	c;

	i = 0;
	info->centroid_min = (t_point){{INFINITY, INFINITY, INFINITY}};
	info->centroid_max = (t_point){{-INFINITY, -INFINITY, -INFINITY}};
	while (i < info->size)
	{
		c = info->builder[info->index_tab[i]].centroid;
		info->centroid_min = vmin(info->centroid_min, c);
		info->centroid_max = vmax(info->centroid_max, c);
		i++;
	}
}

void	get_axis(t_bvh_info *info)
{
	t_point	extent;

	if (info->fallback == true)
		return ;
	extent = vsub(info->centroid_max, info->centroid_min);
	info->axis = 0;
	if (extent.y > extent.x)
		info->axis = 1;
	if (extent.z > extent.data[info->axis])
		info->axis = 2;
}

void	get_cut_pos(t_bvh_info *info, t_bin *bins)
{
	uint8_t	cut;
	double	cost;

	if (info->fallback == true)
		return ;
	auto t_aabb total_bbox = (t_aabb){{{INFINITY, INFINITY, INFINITY}},
		{{INFINITY, INFINITY, INFINITY}}};
	auto size_t i = 0;
	while (i < info->size)
	{
		auto size_t idx = info->index_tab[i];
		total_bbox = union_aabb(total_bbox, info->builder[idx].bbox);
		i++;
	}
	cut = cheapest_cut(bins, &cost);
	auto double leaf_cost = surface_area(total_bbox) * info->size;
	if (cost >= leaf_cost)
		info->fallback = true;
	else
	{
		info->cut_pos = info->centroid_min.data[info->axis]
			+ ((double)(cut + 1) / NBINS)
			* (info->centroid_max.data[info->axis]
				- info->centroid_min.data[info->axis]);
	}
}
