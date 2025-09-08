/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/08 14:18:25 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int32_t	background_color(t_ray *r)
{
	const t_vec	sky_bot = (t_color){{0.42, 0.55, 0.84}};
	const t_vec	sky_top = (t_color){{0.7, 0.8, 1}};

	if (r->dir.y * r->dir.y < 0.02 * 0.02)
		return (vec_to_col(
				lerp_vec(
					sky_bot,
					sky_top,
					(r->dir.y + 0.02) / 0.04
				)
			));
	else if (r->dir.y < 0)
		return (vec_to_col(sky_bot));
	else
		return (vec_to_col(sky_top));
}

int32_t	ray_to_color(t_ray *r, t_elem_lst *elems, size_t frame)
{
	t_hit	hit;
	t_color	color;
	t_color	surface;

	if (!closest_hit(r, elems, &hit, frame))
		return (background_color(r));
	if (hit.mat && hit.mat->bmap != NULL)
		bump_mapping(&hit);
	surface = surface_color(hit.mat->texture, hit.u, hit.v);
	color = ambient_component(&hit, elems, &surface);
	color = vadd(color, diffuse_specular(&hit, elems, &surface, frame));
	return (vec_to_col(color));
}

bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit, size_t frame)
{
	size_t	i;
	bool	did_hit;

	hit->t = INFINITY;
	did_hit = false;
	i = 0;
	while (elems->planes[frame] && elems->planes[frame][i].declared == true)
	{
		did_hit |= hit_plane(elems->planes[frame] + i, r, hit);
		i++;
	}
	if (elems->bvh[frame])
		did_hit |= hit_bvh(elems->bvh[frame], r, hit);
	return (did_hit);
}
