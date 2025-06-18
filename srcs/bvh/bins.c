/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:39:02 by agruet            #+#    #+#             */
/*   Updated: 2025/06/18 16:02:50 by agruet           ###   ########.fr       */
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

	if (info->fallback == true)
		return ;
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

double	surface_area(t_aabb bbox)
{
	const t_point	d = vsub(bbox.max, bbox.min);

	return (2.0 * (d.x * d.y + d.x * d.z + d.y * d.z));
}

void	precompute_right_bins(t_bin *bins, t_bin right_bins[NBINS])
{
	t_aabb	r_bbox;
	size_t	r_count;
	size_t	i;

	r_bbox = (t_aabb){
		.min = {{INFINITY, INFINITY, INFINITY}},
		.max = {{-INFINITY, -INFINITY, -INFINITY}}};
	i = NBINS;
	r_count = 0;
	while (i-- > 0)
	{
		r_bbox = union_aabb(r_bbox, bins[i].bbox);
		r_count += bins[i].count;
		right_bins[i].bbox = r_bbox;
		right_bins[i].count = r_count;
	}
}

uint8_t	cheapest_cut(t_bin *bins, double *out_cost)
{
	t_bin	right_bins[NBINS];

	precompute_right_bins(bins, right_bins);
	auto size_t i = 0;
	auto double best_cost = INFINITY;
	auto uint8_t best_cut = 0;
	auto size_t l_count = 0;
	auto t_aabb l_bbox = (t_aabb){
		.min = {{INFINITY, INFINITY, INFINITY}},
		.max = {{-INFINITY, -INFINITY, -INFINITY}}};
	while (i < NBINS - 1)
	{
		l_bbox = union_aabb(l_bbox, bins[i].bbox);
		l_count += bins[i].count;
		auto double cost = l_count * surface_area(l_bbox)
			+ right_bins[i + 1].count * surface_area(right_bins[i + 1].bbox);
		if (cost < best_cost)
		{
			best_cost = cost;
			best_cut = i;
		}
		i++;
	}
	*out_cost = best_cost;
	return (best_cut);
}
