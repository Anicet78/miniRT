/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:06:58 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:14:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

size_t	*create_first_tab(t_arena *arena, size_t elem_amount)
{
	size_t	*index;
	size_t	count;

	index = arena_calloc(arena, sizeof(size_t) * elem_amount);
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
		i++;
	}
	info->fallback = true;
}

void	calc_branch_sizes(t_bvh_info *info)
{
	size_t	i;
	size_t	idx;
	double	c;

	i = 0;
	if (info->fallback == true)
	{
		calc_fallback(info);
		return ;
	}
	while (i < info->size)
	{
		idx = info->index_tab[i];
		c = info->builder[idx].centroid.data[info->axis];
		if (c < info->cut_pos)
			info->left_size++;
		else
			info->right_size++;
		i++;
	}
	if (info->left_size == 0 || info->right_size == 0)
		calc_fallback(info);
}

void	fallback(t_bvh_info *info)
{
	size_t	i;
	size_t	left_index;
	size_t	right_index;
	size_t	idx;

	i = 0;
	left_index = 0;
	right_index = 0;
	while (i < info->size)
	{
		idx = info->index_tab[i];
		if (i < info->cut_pos)
			info->left[left_index++] = idx;
		else
			info->right[right_index++] = idx;
		i++;
	}
}

void	create_index_tab(t_bvh_info *info)
{
	size_t	i;
	size_t	left_index;
	size_t	right_index;
	size_t	idx;
	double	c;

	info->left = arena_calloc(info->arena, sizeof(size_t) * info->left_size);
	info->right = arena_calloc(info->arena, sizeof(size_t) * info->right_size);
	if (!info->left || !info->right)
		return ;
	if (info->fallback == true)
		return ((void)fallback(info));
	i = 0;
	left_index = 0;
	right_index = 0;
	while (i < info->size)
	{
		idx = info->index_tab[i];
		c = info->builder[idx].centroid.data[info->axis];
		if (c < info->cut_pos)
			info->left[left_index++] = idx;
		else
			info->right[right_index++] = idx;
		i++;
	}
}
