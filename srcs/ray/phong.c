/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/11 16:21:02 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface)
{
	t_color	color;

	color = int_to_tcol(hit->mat->color);
	color = had(color, *surface);
	color = had(
		vmul(
			int_to_tcol(elems->al->color),
			elems->al->ratio
		),
		color
	);
	return (color);
}

bool	shadow_ray(t_ray r, t_elem_lst *elems)
{
	void	*elem;
	uint8_t	type;
	t_hit	hit;

	hit.t = 9999999999;
	elems->count = 0;
	elem = get_next_elem(elems);
	while (elem)
	{
		type = get_elem_type(elem);
		if (type == SPHERE && hit_sphere(elem, &r, &hit))
			return (true);
		else if (type == PLANE && hit_plane(elem, &r, &hit))
			return (true);
		else if (type == CYLINDER && hit_cylinder(elem, &r, &hit))
			return (true);
		elem = get_next_elem(elems);
	}
	return (false);
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
		if (shadow_ray(
				(t_ray){.dir = norm(vsub(lux->pos, hit->p)),
					.p = hit->p},
				elems))
			continue ;
		color = vadd(vmul(vmul(*surface, fmax(0,
			dot(norm(vsub(lux->pos, hit->p)),
			hit->normal))), lux->ratio), color);
		i++;
		lux = elems->lights[i];
	}
	clamp_color(&color);
	return (color);
}
