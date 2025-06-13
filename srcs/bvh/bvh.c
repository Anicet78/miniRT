/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/13 15:37:56 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_builder(t_elem_lst *elems, t_bvh_builder *builder)
{
	void	*elem;
	int		type;
	size_t	count;
	t_aabb	aabb;

	elems->count = 0;
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[0])
	{
		aabb = get_elem_aabb(elem);
		builder[count].bbox = aabb;
		builder[count].obj = elem;
		builder[count].centroid = vmul(vadd(aabb.min, aabb.max), 0.5f);
		elem = get_next_elem(elems);
		count++;
	}
}

void	build_bvh(t_elem_lst *elems, t_bvh_info *prev_info, size_t pos)
{
	t_bvh_info	info;
	t_bin		bins[NBINS];

	if (prev_info->size < 2)
	{
		// create leaf
		return ;
	}
	info.arena = prev_info->arena;
	memset(bins, 0, sizeof(t_bin) * NBINS);
	calc_centroid(&info);
	get_axis(&info);
	fill_bins(bins, &info);
	info.cut_pos = info.centroid_min.data[info.axis] +
					(cheapest_cut(bins) / (double)NBINS) *
					(info.centroid_max.data[info.axis] - info.centroid_min.data[info.axis]);
	calc_branch_sizes(&info);
	create_index_tab(&info);
	if (!info.left || !info.right)
		return ;
	// fallback
	build_bvh(elems, &info, pos * 2 + 1);
	build_bvh(elems, &info, pos * 2 + 2);
	elems->bvh[pos].bbox = union_aabb(elems->bvh[pos + 1].bbox, elems->bvh[pos + 2].bbox);
}

void	create_bvh(t_rt *rt, t_elem_lst *elems)
{
	const size_t	elem_amount = count_elem_amount(elems);
	t_bvh_builder	*builder;
	t_arena			*arena;

	if (elem_amount == 0)
	{
		elems->bvh = NULL;
		return ;
	}
	arena = arena_init(elem_amount * 1000);
	if (!arena)
		(print_err("Memory allocation failed", 0), kill_mlx(rt, 1));
	builder = arena_calloc(arena, sizeof(t_bvh_builder) * elem_amount);
	if (!builder)
		(print_err("Memory allocation failed", 0), clear_arena(&arena),
			kill_mlx(rt, 1));
	init_builder(elems, builder);
	elems->bvh = arena_calloc(arena, sizeof(t_bvh_node)
			* (elem_amount * 2 - 1));
	if (!elems->bvh)
		(print_err("Memory allocation failed", 0), clear_arena(&arena),
			kill_mlx(rt, 1));
	build_bvh(elems, builder, create_first_tab(arena, elem_amount), elem_amount);
	clear_arena(&arena);
}
