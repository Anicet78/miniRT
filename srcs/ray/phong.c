/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/17 18:12:16 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface)
{
	t_color	color;

	color = had(hit->mat->color, *surface);
	color = had(
			vmul(elems->al->color,
				elems->al->ratio),
			color
			);
	return (color);
}

bool	shadow_ray(t_ray r, t_elem_lst *elems, size_t frame)
{
	t_hit	hit;
	size_t	i;

	hit.t = INFINITY;
	i = 0;
	while (elems->planes[frame] && elems->planes[frame][i].declared == true)
	{
		if (hit_plane(elems->planes[frame] + i, &r, &hit))
			return (true);
		i++;
	}
	return (shadow_hit_bvh(elems->bvh[frame], &r, &hit));
}

t_color	lambertian(t_hit *hit, t_elem_lst *elems,
	t_color *surface, size_t frame)
{
	t_color	color;
	t_light	*lux;
	size_t	i;

	color = black_color();
	i = 0;
	lux = elems->lights[frame];
	while (lux->declared == true)
	{
		if (!shadow_ray((t_ray){.dir = norm(vsub(lux->pos, hit->p)),.p = (vadd(hit->p, vmul(hit->normal, 0.000001)))},elems, frame))
			color = vadd(had(vmul(vmul(*surface,fmax(0,dot(norm(vsub(lux->pos, hit->p)),hit->normal))),lux->ratio),lux->color),color);
		i++;
		lux = elems->lights[frame] + i;
	}
	clamp_color(&color);
	return (color);
}
