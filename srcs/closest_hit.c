/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/13 13:27:59 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int32_t	background_color(t_ray *r)
{
	const t_vec	ground = (t_color){0.35, 0.25, 0.15};
	const t_vec	sky_top = (t_color){0.2, 0.5, 0.78};
	const t_vec	sky_bot = (t_color){0.63, 0.72, 0.90};
	float		t;

	if (r->dir.y < 0)
		return (vec_to_col(ground));
	t = r->dir.y * r->dir.y;
	if (t > 1)
		t = 1.0f;
	return (
		vec_to_col(lerp_vec(sky_bot, sky_top, t))
	);
}

int32_t	ray_to_color(t_ray *r, t_elem_lst *elems)
{
	t_hit	hit;

	if (closest_hit(r, elems, &hit))
		return (0x000000);
	return (background_color(r));
}

bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit)
{
	void	*elem;
	int		type;
	bool	did_hit;

	ft_memset(hit, 0, sizeof(t_hit));
	did_hit = false;
	elem = get_next_elem(elems);
	while (elem)
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
