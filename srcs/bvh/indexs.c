/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:06:58 by agruet            #+#    #+#             */
/*   Updated: 2025/06/13 17:12:12 by agruet           ###   ########.fr       */
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

void	calc_fallback(t_bvh_info *info)
{
	size_t	i;

	i = 0;
	info->left_size = 0;
	info->right_size = 0;
	info->cut_pos = info->size / 2;
	while (i < info->size)
	{
		if (i < info->cut_pos)
			info->left_size++;
		else
			info->right_size++;
	}
	info->fallback = true;
}

void	calc_branch_sizes(t_bvh_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->size)
	{
		auto size_t idx = info->index_tab[i];
		auto double c = info->builder[idx].centroid.data[info->axis];
		if (c < info->cut_pos)
			info->left_size++;
		else
			info->right_size++;
	}
	info->fallback = false;
	if (info->left_size == 0 || info->right_size == 0)
		calc_fallback(info);
}

void	fallback(t_bvh_info *info)
{
	size_t	i;
	size_t	left_index;
	size_t	right_index;

	i = 0;
	left_index = 0;
	right_index = 0;
	while (i < info->size)
	{
		if (i < info->cut_pos)
			info->left_size++;
		else
			info->right_size++;
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
	if (info->fallback == true)
	{
		fallback(info);
		return ;
	}
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
