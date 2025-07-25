/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/24 12:38:17 by agruet           ###   ########.fr       */
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
	if (!elems->bvh[frame])
		return (false);
	return (shadow_hit_bvh(elems->bvh[frame], &r, &hit));
}

t_color	light_color(t_hit *hit, t_camera *cam, t_color *surface, t_light *lux)
{
	const t_vec			l = norm(vsub(lux->pos, hit->p));
	t_color				res;
	static const double	shininess = 16;

	res = vadd(vadd(had(vmul(*surface,fmax(0,dot(l,hit->normal)*lux->ratio)),lux->color),black_color()), vmul(lux->color,pow(fmax(0, dot(norm(vsub(vmul(hit->normal, 2 * dot(hit->normal, l)), l)), norm(vsub(cam->pos, hit->p)))), shininess) * lux->ratio));
	return (res);
}

t_color	diffuse_specular(t_hit *hit, t_elem_lst *elems,
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
		if (!shadow_ray((t_ray){.dir = norm(vsub(lux->pos, hit->p)),.p = (vadd(hit->p, vmul(hit->normal, 0.000001)))}, elems, frame))
			color = vadd(light_color(hit, elems->cam, surface, lux),color);
		i++;
		lux = elems->lights[frame] + i;
	}
	clamp_color(&color);
	return (color);
}
