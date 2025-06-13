/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:15:06 by agruet            #+#    #+#             */
/*   Updated: 2025/06/13 16:20:57 by agruet           ###   ########.fr       */
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

void	get_cut_pos(t_bvh_info *info, t_bin *bins)
{
	info->cut_pos = info->centroid_min.data[info->axis] +
					((double)cheapest_cut(bins) / (double)NBINS) *
					(info->centroid_max.data[info->axis]
						- info->centroid_min.data[info->axis]);
}
