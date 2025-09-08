/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:24:28 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 18:05:14 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

void	render(t_rt *rt, t_display *d)
{
	t_ray	r;
	t_point	world_pix;

	d->j = 0;
	while (d->j < d->height)
	{
		d->i = 0;
		while (d->i < d->width)
		{
			world_pix = vadd(d->pixel00,
					vadd(vmul(d->pix_du, d->i), vmul(d->pix_dv, d->j)));
			r.dir = norm(vsub(world_pix, rt->elements.cam.pos));
			r.p = rt->elements.cam.pos;
			put_pixel_to_img(&rt->mlx, d->i, d->j,
				ray_to_color(&r, &rt->elements));
			d->i += 1;
		}
		d->j += 1;
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
		rt->mlx.img, 0, 0);
}
