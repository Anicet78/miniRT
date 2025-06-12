/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:39:02 by agruet            #+#    #+#             */
/*   Updated: 2025/06/12 15:11:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	get_bin_index(double coord, double min_coord, double max_coord, int nbins)
{
	const double	normalized = (coord - min_coord) / (max_coord - min_coord);
	int				index;

	index = (int)(normalized * nbins);
	if (index == nbins)
		index = nbins - 1;
	return (index);
}

uint8_t	fill_bins(t_bvh_builder *builder, t_bin bins[8], size_t *indexs, size_t size)
{
	auto size_t i = 0;
	auto t_point centroid_min = {INFINITY, INFINITY, INFINITY};
	auto t_point centroid_max = {-INFINITY, -INFINITY, -INFINITY};
	while (i < size)
	{
		auto const t_point c = builder[indexs[i++]].centroid;
		centroid_min = vmin(centroid_min, c);
		centroid_max = vmin(centroid_max, c);
	}
	auto const t_point extent = vsub(centroid_max, centroid_min);
	auto uint8_t axis = 0;
	if (extent.y > extent.x)
		axis = 1;
	if (extent.z > extent.data[axis])
		axis = 2;
	i = 0;
	while (i < size)
	{
		auto const double coord = builder[indexs[i]].centroid.data[axis];
		auto const int index = get_bin_index(coord, centroid_min.data[axis],
			centroid_max.data[axis], NBINS);
		bins[index].count++;
		bins[index].bbox = union_aabb(bins[index].bbox, builder[indexs[i++]].bbox);
	}
	return (axis);
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
