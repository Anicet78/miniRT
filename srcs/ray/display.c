/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:20 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/08 16:59:33 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_display	init_display(t_camera *cam)
{
	t_display	ret;

	cam->fov = fmin(cam->fov, 179.9999999);
	cam->fov *= PI / 180;
	ret.width = WIDTH;
	ret.height = ft_max((int)(WIDTH * (1 / (16.0 / 9.0))), 1);
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
	ret.vp_upleft = vsub(ret.vp_upleft,
			vadd(vmul(ret.vp_u, 0.5), vmul(ret.vp_v, 0.5)));
	ret.pixel00 = vadd(ret.vp_upleft, vmul(vadd(ret.pix_du, ret.pix_dv), 0.5));
	return (ret);
}
