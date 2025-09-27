/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:53:06 by agruet            #+#    #+#             */
/*   Updated: 2025/09/27 14:59:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

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
