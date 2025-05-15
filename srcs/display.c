/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:20 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/15 13:53:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_display	init_display(t_camera *cam)
{
	t_display	ret;

	cam->fov = mind(cam->fov, 179.9999999);
	cam->fov *= PI / 180;
	ret.width = WIDTH;
	ret.height = max((int)(WIDTH * (1 / ASPECT_RATIO)), 1);
	ret.focal_len = 1.0;
	ret.vp_width = 2 * tan(cam->fov / 2);
	ret.vp_height = ret.vp_width * ((double)ret.height / (double)ret.width);
	if (fabs(dot(cam->dir, up_v())) == 1.0)
		ret.vp_u = norm(cross_prod(cam->dir, right_v()));
	else
	{
		ret.vp_u = cross_prod(cam->dir, up_v());
		ret.vp_u = vmul(norm(ret.vp_u), ret.vp_width);
	}
	ret.vp_v = vmul(norm(cross_prod(cam->dir, ret.vp_u)), ret.vp_height);
	ret.pix_du = vdiv(ret.vp_u, (double)ret.width);
	ret.pix_dv = vdiv(ret.vp_v, (double)ret.height);
	ret.vp_upleft = vadd(cam->pos, cam->dir);
	ret.vp_upleft = vsub(ret.vp_upleft, vadd(vmul(ret.vp_u, 0.5), vmul(ret.vp_v, 0.5)));
	ret.pixel00 = vadd(ret.vp_upleft, vmul(vadd(ret.pix_du, ret.pix_dv), 0.5));
	return (ret);
}

void	render_display(t_rt *rt, t_display *d)
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
			put_pixel_to_img(&(rt->mlx), rt->mlx.addr[0], (uint32_t[2]){d->i, d->j}, ray_to_color(&r, &rt->elements, SIZE_MAX));
			d->i += 1;
		}
		d->j += 1;
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
		rt->mlx.imgs[0], 0, 0);
}
