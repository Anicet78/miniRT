/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/18 12:53:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	init_info(t_bvh_info *info, t_bvh_info *prev_info, size_t pos)
{
	info->arena = prev_info->arena;
	info->builder = prev_info->builder;
	info->fallback = false;
	if (pos % 2 == 1)
	{
		info->index_tab = prev_info->left;
		info->size = prev_info->left_size;
	}
	else
	{
		info->index_tab = prev_info->right;
		info->size = prev_info->right_size;
	}
	info->left_size = 0;
	info->right_size = 0;
}

size_t	get_next(size_t pos)
{
	size_t	i;

	if (pos == 0)
		return (2);
	i = pos;
	while (i != 0 && i % 2 == 0)
		i = (i - 1) / 2;
	if (i == 0)
		return (0);
	return ((i - 1) / 2 * 2 + 2);
}

size_t	create_leaf(t_bvh_node *bvh, t_bvh_info *info, size_t pos)
{
	t_bvh_builder	elem;

	elem.obj = NULL;
	bvh[pos].is_leaf = true;
	if (info->size < 1)
		return (pos);
	elem = info->builder[info->index_tab[0]];
	bvh[pos].next = get_next(pos);
	bvh[pos].bbox = elem.bbox;
	bvh[pos].obj = elem.obj;
	if (pos == 0)
		return (1);
	return (pos);
}

size_t	build_bvh(t_bvh_node *bvh, t_bvh_info *prev_info, size_t pos)
{
	t_bvh_info	info;
	t_bin		bins[NBINS];

	init_info(&info, prev_info, pos);
	if (info.size <= 1)
		return (create_leaf(bvh, &info, pos));
	ft_memset(bins, 0, sizeof(t_bin) * NBINS);
	calc_centroid(&info);
	get_axis(&info);
	fill_bins(bins, &info);
	get_cut_pos(&info, bins);
	calc_branch_sizes(&info);
	create_index_tab(&info);
	if (!info.left || !info.right)
		return (0);
	bvh[pos].next = get_next(pos);
	bvh[pos].left = build_bvh(bvh, &info, pos * 2 + 1);
	bvh[pos].right = build_bvh(bvh, &info, pos * 2 + 2);
	if (bvh[pos].left == 0 || bvh[pos].right == 0)
		return (0);
	bvh[pos].bbox = union_aabb(bvh[pos * 2 + 1].bbox, bvh[pos * 2 + 2].bbox);
	if (pos == 0)
		return (1);
	return (pos);
}

static bool	create_bvh(t_rt *rt, t_elem_lst *elems, size_t frame)
{
	const size_t	elem_amount = count_elem_amount(elems, frame);
	t_bvh_builder	*builder;
	t_arena			*arena;
	size_t			bvh;

	if (elem_amount == 0)
		return (true);
	arena = arena_init(elem_amount * 1000);
	if (!arena)
		return (false);
	builder = arena_calloc(arena, sizeof(t_bvh_builder) * elem_amount);
	if (!builder)
		return (clear_arena(&arena), false);
	init_builder(elems, builder, frame);
	elems->bvh[frame] = arena_calloc(rt->arena, sizeof(t_bvh_node)
			* (elem_amount * 2 - 1));
	if (!elems->bvh[frame])
		return (clear_arena(&arena), false);
	bvh = build_bvh(elems->bvh[frame], &(t_bvh_info){.arena = arena,
			.builder = builder,
			.right = create_first_tab(arena, elem_amount),
			.right_size = elem_amount}, 0);
	clear_arena(&arena);
	return (bvh != 0);
}

void	create_all_bvh(t_rt *rt)
{
	t_elem_lst	*elems;
	size_t		i;

	elems = &rt->elements;
	i = 0;
	elems->bvh = arena_calloc(rt->arena, sizeof(t_bvh_node *)
			* elems->frame_amount);
	if (!elems->bvh)
	{
		print_err("Memory allocation failed", 0);
		kill_mlx(rt, EXIT_FAILURE);
	}
	while (i < elems->frame_amount)
	{
		if (create_bvh(rt, elems, i) == false)
		{
			print_err("Memory allocation failed", 0);
			kill_mlx(rt, EXIT_FAILURE);
		}
		i++;
	}
}
