/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:19 by agruet            #+#    #+#             */
/*   Updated: 2025/09/27 15:02:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static
t_vec	sample_square(uint64_t sample_index, uint64_t total_samples)
{
	const uint64_t	n = (uint64_t)ceil(sqrt((double)total_samples));
	const uint64_t	i = sample_index % n;
	const uint64_t	j = sample_index / n;

	return (t_vec){{(i + 0.5) / n - 0.5, (j + 0.5) / n - 0.5, 0}};
}

static inline
t_vec	get_world_pix(const t_display *d, uint64_t infos[4])
{
	const t_vec	offset = sample_square(infos[2], infos[3]);

	return (vadd(d->pixel00,
			vadd(vmul(d->pix_du, offset.x + (double)infos[0]),
				vmul(d->pix_dv, offset.y + (double)infos[1]))));
}

t_ray	get_ray(const t_display *d, uint64_t infos[4],
	size_t img_index, t_params *p)
{
	t_point				world_pix;
	t_ray				r;

	world_pix = get_world_pix(d, infos);
	r.dir = norm(vsub(world_pix, p->elements.cam[img_index].pos));
	r.p = p->elements.cam[img_index].pos;
	return (r);
}

void	aa_create_rays(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_color			pixel_col;
	uint64_t		sample;
	t_ray			r;
	static double	ratio = 0;

	if (ratio == 0)
		ratio = 1.0 / (double)p->elements.aliasing;
	pixel_col = (t_vec){{0, 0, 0}};
	sample = 0;
	while (sample < p->elements.aliasing)
	{
		r = get_ray(d,
			(uint64_t[4]){coords[0], coords[1], sample, p->elements.aliasing},
			img_index, p);
		pixel_col = vadd(pixel_col, ray_to_color(&r, &p->elements, img_index));
		sample++;
	}
	put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
		vec_to_col(vmul(pixel_col, ratio)));
}
