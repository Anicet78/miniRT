/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:19 by agruet            #+#    #+#             */
/*   Updated: 2025/09/27 01:30:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

bool	is_col_far(t_color col1, t_color col2)
{
	col1 = vsub(col1, col2);
	return (dot(col1, col1) > AA_THRESHOLD);
}

bool	aa_early_exit(t_color diff[AA_EARLY_EXIT])
{
	uint64_t	i;

	if (AA_EARLY_EXIT <= 1)
		return (true);
	i = 0;
	while (i < (uint64_t)(AA_EARLY_EXIT - 1))
	{
		if (is_col_far(diff[i], diff[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

void	aa_create_rays(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_color			pixel_color;
	uint64_t		sample;
	t_ray			r;
	static double	ratio = 0;
	t_color			diff[AA_EARLY_EXIT];

	auto t_color ray_color;
	if (ratio == 0)
		ratio = 1.0 / (double)p->elements.aliasing;
	pixel_color = (t_vec){{0, 0, 0}};
	sample = 0;
	while (sample < p->elements.aliasing)
	{
		r = get_ray(d, (uint64_t[4]){coords[0], coords[1], sample, p->elements.aliasing}, img_index, p);
		ray_color = ray_to_color(&r, &p->elements, img_index);;
		if (sample < AA_EARLY_EXIT)
			diff[sample] = ray_color;
		pixel_color = vadd(pixel_color, ray_color);
		sample++;
		if (sample == AA_EARLY_EXIT && aa_early_exit(diff))
			return ((void)(put_pixel_to_img(p->mlx, p->mlx->addr[img_index],
				coords, vec_to_col(vdiv(pixel_color, AA_EARLY_EXIT)))));
	}
	put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
		vec_to_col(vmul(pixel_color, ratio)));
}
