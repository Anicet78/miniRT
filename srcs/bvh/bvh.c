/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/11 18:27:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

size_t	count_elem_amount(t_elem_lst *elems)
{
	void	*elem;
	size_t	count;

	elems->count = 0;
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[0])
	{
		count++;
		elem = get_next_elem(elems);
	}
	return (count);
}

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

void	create_bvh(t_rt *rt, t_elem_lst *elems)
{
	const size_t	elem_amount = count_elem_amount(elems);
	t_bvh_builder	*builder;
	t_bin			bins[NBINS];
	void			*elem;

	auto t_arena *arena = arena_init(elem_amount * 1000);
	if (!arena)
		(print_err("Memory allocation failed", 0), kill_mlx(rt, 1));
	builder = arena_calloc(arena, sizeof(t_bvh_builder) * elem_amount);
	if (!builder)
		(print_err("Memory allocation failed", 0), kill_mlx(rt, 1));
	init_builder(elems, builder);
	memset(bins, 0, sizeof(t_bin) * NBINS);
	auto uint8_t axis = fill_bins(builder, bins, elem_amount);
	auto uint8_t cut = cheapest_cut(bins);
	elems->bvh = arena_calloc(arena, sizeof(t_bvh_node)
			* (elem_amount * 2 - 1));
	if (!elems->bvh)
		(print_err("Memory allocation failed", 0), kill_mlx(rt, 1));
}
