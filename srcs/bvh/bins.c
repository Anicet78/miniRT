/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:39:02 by agruet            #+#    #+#             */
/*   Updated: 2025/06/16 15:42:12 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	get_bin_index(double coord, double min_coord, double max_coord, int nbins)
{
	double	normalized;
	int		index;

	if (min_coord == max_coord)
		return (0);
	normalized = (coord - min_coord) / (max_coord - min_coord);
	index = (int)(normalized * nbins);
	if (index == nbins)
		index = nbins - 1;
	return (index);
}

void	fill_bins(t_bin bins[8], t_bvh_info *info)
{
	size_t	i;
	double	coord;
	int		index;

	i = 0;
	while (i < info->size)
	{
		coord = info->builder[info->index_tab[i]].centroid.data[info->axis];
		index = get_bin_index(coord, info->centroid_min.data[info->axis],
				info->centroid_max.data[info->axis], NBINS);
		bins[index].count++;
		bins[index].bbox = union_aabb(bins[index].bbox,
				info->builder[info->index_tab[i]].bbox);
		i++;
	}
}

static double	surface_area(t_aabb bbox)
{
	const t_point	d = vsub(bbox.max, bbox.min);

	return (2.0 * (d.x * d.y + d.x * d.z + d.y * d.z));
}

uint8_t	cheapest_cut(t_bin *bins)
{
	uint8_t	cut;
	double	cost;
	double	cheapest;

	if (NBINS < 2)
		return (0);
	cheapest = surface_area(bins[0].bbox) * bins[0].count
		+ surface_area(bins[1].bbox) * bins[1].count;
	cut = 1;
	while (cut + 1 < NBINS)
	{
		cost = surface_area(bins[cut].bbox) * bins[cut].count
			+ surface_area(bins[cut + 1].bbox) * bins[cut + 1].count;
		if (cost < cheapest)
			cheapest = cost;
		cut++;
	}
	return (cheapest);
}
