/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/29 16:08:02 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit)
{
	bool	did_hit;
	void	*elem;
	int		type;

	hit->t = INFINITY;
	did_hit = false;
	elems->count = 0;
	elem = get_next_elem(elems);
	while (elem)
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

int32_t	ray_to_color(t_ray *r, t_elem_lst *elems)
{
	t_hit	hit;
	t_color	color;

	if (!closest_hit(r, elems, &hit))
		return (background_color(r));
	color = ambient_component(&hit, elems);
	color = vadd(color, diffuse_specular(&hit, elems, hit.color));
	return (vec_to_col(color));
}
