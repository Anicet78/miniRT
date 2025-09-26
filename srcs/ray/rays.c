/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:53:06 by agruet            #+#    #+#             */
/*   Updated: 2025/09/27 01:17:34 by agruet           ###   ########.fr       */
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

void	create_rays(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_ray	r;

	if (p->elements.aliasing != 1)
	{
		aa_create_rays(d, coords, img_index, p);
		return ;
	}
	r = (t_ray){.dir = norm(vsub(vadd(d->pixel00,
						vadd(vmul(d->pix_du, coords[0]),
					vmul(d->pix_dv, coords[1]))),
						p->elements.cam[img_index].pos)),
	.p = p->elements.cam[img_index].pos};
	put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
		vec_to_col(ray_to_color(&r, &p->elements, img_index)));
}
