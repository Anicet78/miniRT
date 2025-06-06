/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
<<<<<<<< HEAD:srcs/raytraceur/closest_hit.c
/*   Updated: 2025/06/05 16:35:03 by agruet           ###   ########.fr       */
========
/*   Updated: 2025/06/06 17:19:25 by tgallet          ###   ########.fr       */
>>>>>>>> origin/triste:srcs/ray/closest_hit.c
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int32_t	background_color(t_ray *r)
{
	const t_vec	sky_bot = (t_color){0.42, 0.55, 0.84};
	const t_vec	sky_top = (t_color){0.7, 0.8, 1};

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
		return (0x0);
		// return (background_color(r));
	surface = surface_color(hit.mat->texture, hit.u, hit.v);
	color = ambient_component(&hit, elems, &surface);
	color = vadd(color, lambertian(&hit, elems, &surface));
	return (vec_to_col(color));
}

bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit, size_t frame)
{
	void	*elem;
	uint8_t	type;
	bool	did_hit;

	// ft_memset(hit, 0, sizeof(t_hit));
	hit->t = 9999999999;
	did_hit = false;
	elems->count = 0;
	if (frame > 0)
		elems->count = elems->frames[frame - 1];
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[frame])
	{
		type = get_elem_type(elem);
		if (type == SPHERE)
			did_hit |= hit_sphere(elem, r, hit);
		else if (type == PLANE)
			did_hit |= hit_plane(elem, r, hit);
		else if (type == CYLINDER)
			did_hit |= hit_cylinder(elem, r, hit);
		elem = get_next_elem(elems);
	}
	return (did_hit);
}
