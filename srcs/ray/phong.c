/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/10/01 14:12:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

t_color	ambient_component(t_elem_lst *elems,
	t_color *surface, size_t frame)
{
	t_color	color;

	color = had(
			vmul(elems->al[frame].color,
				elems->al[frame].ratio),
			*surface
			);
	return (color);
}

bool	shadow_ray(t_ray r, t_elem_lst *elems, size_t frame, double dist)
{
	t_hit	hit;
	size_t	i;

	hit.t = INFINITY;
	i = 0;
	while (elems->planes[frame] && elems->planes[frame][i].declared == true)
	{
		if (hit_plane(elems->planes[frame] + i, &r, &hit) && hit.t < dist)
			return (true);
		i++;
	}
	if (!elems->bvh[frame])
		return (false);
	return (shadow_hit_bvh(elems->bvh[frame], &r, &hit, dist));
}

t_color	light_color(t_hit *hit, t_camera *cam, t_color *surface, t_light *lux)
{
	const t_vec			l = norm(vsub(lux->pos, hit->p));
	t_color				res;

	res = vadd(vadd(had(vmul(*surface,
						fmax(0, dot(l, hit->normal) * lux->ratio)),
					lux->color), black_color()), vmul(lux->color,
				pow(fmax(0, dot(norm(vsub(vmul(hit->normal,
										2 * dot(hit->normal, l)), l)),
							norm(vsub(cam->pos, hit->p)))), SHININESS
					) * lux->ratio));
	return (res);
}

t_color	diffuse_specular(t_hit *hit, t_elem_lst *elems,
	t_color *surface, size_t frame)
{
	t_color	color;
	t_light	*lux;
	t_ray	rayman;
	t_vec	to_lux;

	color = black_color();
	lux = elems->lights[frame];
	while (lux->declared == true)
	{
		to_lux = vsub(lux->pos, hit->p);
		rayman = (t_ray){.dir = norm(to_lux),
			.p = vadd(hit->p, vmul(hit->normal, 0.0001))};
		if (!shadow_ray(rayman, elems, frame, magn(to_lux)))
			color = vadd(light_color(hit, elems->cam, surface, lux), color);
		lux += 1;
	}
	clamp_color(&color);
	return (color);
}
