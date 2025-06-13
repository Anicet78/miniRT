/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:15:06 by agruet            #+#    #+#             */
/*   Updated: 2025/06/13 15:29:09 by agruet           ###   ########.fr       */
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

void	calc_centroid(t_bvh_info *info)
{
	size_t	i;

	i = 0;
	info->centroid_min = (t_point){INFINITY, INFINITY, INFINITY};
	info->centroid_max = (t_point){-INFINITY, -INFINITY, -INFINITY};
	while (i < info->size)
	{
		auto const t_point c = info->builder[info->index_tab[i++]].centroid;
		info->centroid_min = vmin(info->centroid_min, c);
		info->centroid_max = vmax(info->centroid_max, c);
	}
}

void	get_axis(t_bvh_info *info)
{
	const t_point	extent = vsub(info->centroid_max, info->centroid_min);

	info->axis = 0;
	if (extent.y > extent.x)
		info->axis = 1;
	if (extent.z > extent.data[info->axis])
		info->axis = 2;
}

void	calc_branch_sizes(t_bvh_info *info)
{
	size_t	i;
	size_t	left_count;
	size_t	right_count;

	i = 0;
	left_count = 0;
	right_count = 0;
	while (i < info->size)
	{
		auto size_t idx = info->index_tab[i];
		auto double c = info->builder[idx].centroid.data[info->axis];
		if (c < info->cut_pos)
			left_count++;
		else
			right_count++;
	}
}

void	create_index_tab(t_bvh_info *info)
{
	size_t	i;
	size_t	left_index;
	size_t	right_index;

	info->left = arena_calloc(info->arena, sizeof(size_t) * info->left_size);
	info->right = arena_calloc(info->arena, sizeof(size_t) * info->right_size);
	if (!info->left || !info->right)
		return ;
	i = 0;
	left_index = 0;
	right_index = 0;
	while (i < info->size)
	{
		auto size_t idx = info->index_tab[i];
		auto double c = info->builder[idx].centroid.data[info->axis];
		if (c < info->cut_pos)
			info->left[left_index++] = idx;
		else
			info->right[right_index++] = idx;
	}
}
