/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:06:58 by agruet            #+#    #+#             */
/*   Updated: 2025/06/13 16:24:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	// fallback
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
