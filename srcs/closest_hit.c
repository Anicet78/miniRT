/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/19 13:59:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int32_t	background_color(t_ray *r)
{
	const t_vec	sky_top = (t_color){0.5, 0.65, 0.84};
	const t_vec	sky_bot = (t_color){0.63, 0.72, 0.90};

	if (r->dir.y < 0)
		return (vec_to_col(sky_top));
	else
		return (vec_to_col(sky_bot));
}

int32_t	ray_to_color(t_ray *r, t_elem_lst *elems, size_t frame_end)
{
	t_hit	hit;

	if (closest_hit(r, elems, &hit, frame_end))
		return (hit.mat->color);
	return (background_color(r));
}

bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit, size_t frame_end)
{
	void	*elem;
	uint8_t	type;
	bool	did_hit;

	ft_memset(hit, 0, sizeof(t_hit));
	hit->t = 9999999999;
	did_hit = false;
	elems->count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= frame_end)
	{
		type = get_elem_type(elem);
		if (type == AMBIENT_LIGHTING || type == LIGHT || type == CAMERA)
			;
		else if (type == SPHERE)
			did_hit |= hit_sphere(elem, r, hit);
		else if (type == PLANE)
			did_hit |= hit_plane(elem, r, hit);
		else if (type == CYLINDER)
			did_hit |= hit_cylinder(elem, r, hit);
		elem = get_next_elem(elems);
	}
	return (did_hit);
}
