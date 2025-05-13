/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:20 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/13 05:29:11 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_dis	init_display(t_camera *cam)
{
	t_dis	ret;

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
	ret.vp_v = vmul(norm(cross_prod(ret.vp_u, cam->dir)), ret.vp_height);
	ret.pix_du = vdiv(ret.vp_u, (double)ret.width);
	ret.pix_dv = vdiv(ret.vp_v, (double)ret.height);
	ret.vp_upleft = vadd(cam->pos, cam->dir);
	ret.vp_upleft = vsub(ret.vp_upleft, vadd(vmul(ret.vp_u, 0.5), vmul(ret.vp_v, 0.5)));
	ret.pixel00 = vadd(ret.vp_upleft, vmul(vadd(ret.pix_du, ret.pix_dv), 0.5));
	return (ret);
}

void	display(t_miniRT *rt, t_dis *d)
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
			// add closest hit and coloring
			d->i += 1;
		}
		d->j += 1;
	}
}

