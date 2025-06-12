/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/12 15:10:36 by agruet           ###   ########.fr       */
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

size_t	*create_first_tab(t_arena *arena, size_t elem_amount)
{
	size_t	*index;
	size_t	count;

	index = arena_calloc(arena, elem_amount);
	if (!index)
		return (NULL);
	count = 0;
	while (count < elem_amount)
	{
		index[count] = count;
		count++;
	}
	return (index);
}

void	init_builder(t_elem_lst *elems, t_bvh_builder *builder, t_arena *arena)
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
		builder[count].arena = arena;
		elem = get_next_elem(elems);
		count++;
	}
}

void	build_bvh(t_elem_lst *elems, t_bvh_builder *builder, size_t *index, size_t size, size_t bvh_index)
{
	if (size < 2)
	{
		// create leaf
		return ;
	}
	auto t_bin bins[NBINS];
	memset(bins, 0, sizeof(t_bin) * NBINS);
	auto uint8_t axis = fill_bins(builder, bins, index, size);
	auto uint8_t cut = cheapest_cut(bins);
	auto size_t count_left = 0;
	auto size_t count_right = 0;
	auto size_t i = 0;
	auto t_point centroid_min = {INFINITY, INFINITY, INFINITY};
	auto t_point centroid_max = {-INFINITY, -INFINITY, -INFINITY};
	while (i < size)
	{
		auto const t_point c = builder[index[i++]].centroid;
		centroid_min = vmin(centroid_min, c);
		centroid_max = vmin(centroid_max, c);
	}
	i = 0;
	while (i < size)
	{
		auto const double coord = builder[index[i]].centroid.data[axis];
		auto const int index = get_bin_index(coord, centroid_min.data[axis],
			centroid_max.data[axis], NBINS);
		if (index <= cut)
			count_left++;
		else
			count_right++;
		i++;
	}
	auto size_t *left = arena_calloc(builder[0].arena, sizeof(size_t) * count_left);
	auto size_t *right = arena_calloc(builder[0].arena, sizeof(size_t) * count_right);
	if (!left || !right)
		return ;
	i = 0;
	auto size_t left_index = 0;
	auto size_t right_index = 0;
	while (i < size)
	{
		auto const double coord = builder[index[i]].centroid.data[axis];
		auto const int index = get_bin_index(coord, centroid_min.data[axis],
			centroid_max.data[axis], NBINS);
		if (index <= cut)
			left[left_index++] = i;
		else
			right[right_index++] = i;
		i++;
	}
	elems->bvh[bvh_index] = {.bbox = };
	build_bvh(elems, builder, left, count_left, bvh_index + 1);
	build_bvh(elems, builder, right, count_right, bvh_index + 2);
}

void	create_bvh(t_rt *rt, t_elem_lst *elems)
{
	const size_t	elem_amount = count_elem_amount(elems);
	t_bvh_builder	*builder;

	if (elem_amount == 0)
	{
		elems->bvh = NULL;
		return ;
	}
	auto t_arena *arena = arena_init(elem_amount * 1000);
	if (!arena)
		(print_err("Memory allocation failed", 0), kill_mlx(rt, 1));
	builder = arena_calloc(arena, sizeof(t_bvh_builder) * elem_amount);
	if (!builder)
		(print_err("Memory allocation failed", 0), clear_arena(&arena),
			kill_mlx(rt, 1));
	init_builder(elems, builder, arena);
	elems->bvh = arena_calloc(arena, sizeof(t_bvh_node)
			* (elem_amount * 2 - 1));
	if (!elems->bvh)
		(print_err("Memory allocation failed", 0), clear_arena(&arena),
			kill_mlx(rt, 1));
	build_bvh(elems, builder, create_first_tab(arena, elem_amount), elem_amount);
	clear_arena(&arena);
}
