/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:38:23 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/14 22:46:51 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool intersect_cylinder_body(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	const t_vec		oc = vsub(r->p, cylinder->pos);
	const double	a = dot(r->dir, r->dir) - pow(dot(r->dir, cylinder->axis), 2);
	const double	b = 2 * (dot(r->dir, oc) - dot(r->dir, cylinder->axis) * dot(oc, cylinder->axis));
	const double	c = dot(oc, oc) - pow(dot(oc, cylinder->axis), 2) - pow(cylinder->radius, 2);
	const double	delta = b * b - 4 * a * c;
	double 			t;
	double			height_proj;

	if (delta < 0)
		return (false);
	t = (-b - sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
		return (false);
	hit->t = t;
	hit->p = vadd(r->p, vmul(r->dir, hit->t));
	height_proj = dot(vsub(hit->p, cylinder->pos), cylinder->axis);
	if (height_proj < -cylinder->height / 2 || height_proj > cylinder->height / 2)
		return (false);
	return (true);
}

bool intersect_cylinder_caps(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	return (false);
}

void set_hit_info(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	t_vec	hit_to_center = vsub(hit->p, cylinder->pos);
	t_vec	proj_axis = vmul(cylinder->axis, dot(hit_to_center, cylinder->axis));
	double	height_proj;

	hit->normal = norm(vsub(hit_to_center, proj_axis));
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->mat = &cylinder->mat;
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	height_proj = dot(vsub(hit->p, cylinder->pos), cylinder->axis);
	hit->v = (height_proj + cylinder->height / 2) / cylinder->height;
}

bool hit_cylinder(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	if (intersect_cylinder_body(cylinder, r, hit))
	{
		set_hit_info(cylinder, r, hit);
		return (true);
	}
	if (intersect_cylinder_caps(cylinder, r, hit))
	{
		set_hit_info(cylinder, r, hit);
		return (true);
	}
	return (false);
}
