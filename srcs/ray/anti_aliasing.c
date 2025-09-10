/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:19 by agruet            #+#    #+#             */
/*   Updated: 2025/09/10 12:57:15 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static inline
double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

static
t_vec	sample_square(void)
{
	return ((t_vec){{random_double() - 0.5, random_double() - 0.5, 0}});
}

static inline
t_vec	get_world_pix(const t_display *d, uint32_t x, uint32_t y)
{
	const t_vec	offset = sample_square();

	return (vadd(d->pixel00,
			vadd(vmul(d->pix_du, offset.x + (double)x),
				vmul(d->pix_dv, offset.y + (double)y))));
}

static
t_ray	get_ray(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_point				world_pix;
	t_ray				r;
	const uint32_t		x = coords[0];
	const uint32_t		y = coords[1];

	if (p->elements.aliasing == 1)
		world_pix = vadd(d->pixel00, vadd(vmul(d->pix_du, x),
					vmul(d->pix_dv, y)));
	else
		world_pix = get_world_pix(d, x, y);
	r.dir = norm(vsub(world_pix, p->elements.cam[img_index].pos));
	r.p = p->elements.cam[img_index].pos;
	return (r);
}

void	create_rays(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_color			pixel_color;
	uint64_t		sample;
	t_ray			r;
	static double	ratio = 0;

	if (ratio == 0)
		ratio = 1.0 / (double)p->elements.aliasing;
	pixel_color = (t_vec){{0, 0, 0}};
	sample = 0;
	while (sample < p->elements.aliasing)
	{
		r = get_ray(d, coords, img_index, p);
		pixel_color = vadd(pixel_color,
				ray_to_color(&r, &p->elements, img_index));
		sample++;
	}
	put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
		vec_to_col(vmul(pixel_color, ratio)));
}
