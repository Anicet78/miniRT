/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/29 16:08:15 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

t_color	ambient_component(t_hit *hit, t_elem_lst *elems)
{
	t_color	color;

	color = had(
			vmul(elems->amb.color,
				elems->amb.ratio),
			*hit->color
			);
	return (color);
}

bool	shadow_ray(t_ray r, t_elem_lst *elems, double dist)
{
	t_hit	hit;
	void	*elem;
	int		type;

	hit.t = INFINITY;
	elem = get_next_elem(elems);
	while (elem)
	{
		type = get_elem_type(elem);
		if (type == SPHERE)
		{
			if (hit_sphere(elem, &r, &hit) && hit.t < dist)
				return (true);
		}
		else if (type == PLANE)
		{
			if (hit_plane(elem, &r, &hit) && hit.t < dist)
				return (true);
		}
		else if (type == CYLINDER && hit_cylinder(elem, &r, &hit)
			&& hit.t < dist)
			return (true);
		elem = get_next_elem(elems);
	}
	return (false);
}

t_color	light_color(t_hit *hit, t_camera *cam, t_color *surface, t_light *lux)
{
	const t_vec			l = norm(vsub(lux->pos, hit->p));
	t_color				res;
	static const double	shininess = 64;

	res = vadd(vadd(had(vmul(*surface,
						fmax(0, dot(l, hit->normal) * lux->ratio)),
					lux->color), black_color()), vmul(lux->color,
				pow(fmax(0, dot(norm(vsub(vmul(hit->normal,
										2 * dot(hit->normal, l)), l)),
							norm(vsub(cam->pos, hit->p)))), shininess
					) * lux->ratio));
	return (res);
}

t_color	diffuse_specular(t_hit *hit, t_elem_lst *elems,
	t_color *obj_col)
{
	t_color	color;
	t_light	*lux;
	t_ray	rayman;
	t_vec	to_lux;

	elems->count = 0;
	color = black_color();
	lux = &elems->light;
	to_lux = vsub(lux->pos, hit->p);
	rayman = (t_ray){.dir = norm(to_lux),
		.p = vadd(hit->p, vmul(hit->normal, 0.000001))};
	if (!shadow_ray(rayman, elems, magn(to_lux)))
		color = vadd(light_color(hit, &elems->cam, obj_col, lux), color);
	clamp_color(&color);
	return (color);
}
