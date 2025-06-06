/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:57:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/29 01:07:38 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	hit_sphere(t_sphere *sphere, t_ray *r, t_hit *hit)
{
	const double	a = dot(r->dir, r->dir);
	const double	b = 2 * dot(r->dir, vsub(r->p, sphere->pos));
	const double	c = dot(vsub(r->p, sphere->pos), vsub(r->p, sphere->pos))
						- sphere->radius * sphere->radius;
	const double	delta = b * b - 4 * a * c;
	double			t;

	if (delta < 0)
		return (false);
	t = (-b - sqrt(delta)) / (2 * a);
	if (hit->t < t)
		return (false);
	hit->t = t;
	hit->p = vadd(r->p, vmul(r->dir, hit->t));
	hit->normal = norm(vsub(hit->p, sphere->pos));
	hit->mat = &sphere->mat;
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->u = (atan2(hit->normal.z, hit->normal.x) / (2 * PI)) + 0.5;
	hit->v =  0.5 - (asin(hit->normal.y) / PI);
	return (true);
}

bool	hit_plane(t_plane *plane, t_ray *r, t_hit *hit)
{
	const double	denom = dot(plane->normal, r->dir);
	double			t;

	if (fabs(denom) < 0.000001)
		return (false);
	t = dot(vsub(plane->pos, r->p), plane->normal) / denom;
	if (t < 0 || hit->t < t)
		return (false);
	hit->p = vadd(r->p, vmul(r->dir, t));
	hit->t = t;
	hit->u = fmod(hit->p.x - plane->pos.x, 4);
	hit->v = fmod(hit->p.y - plane->pos.y, 4);
	hit->front = (denom < 0);
	hit->mat = &plane->mat;
	hit->normal = plane->normal;
	return (true);
}

/*
bool	hit_cylinder(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	const t_vec	oc = vsub(r->p, cylinder->pos);
	const double	a = dot(r->dir, r->dir) - pow(dot(r->dir, cylinder->axis), 2);
	const double	b = 2 * (dot(r->dir, oc) - dot(r->dir, cylinder->axis) * dot(oc, cylinder->axis));
	const double	c = dot(oc, oc) - pow(dot(oc, cylinder->axis), 2) - pow(cylinder->radius, 2);
	const double	delta = b * b - 4 * a * c;
	double			t;

	if (delta < 0)
	return (false);
	t = (-b - sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
	return (false);
	hit->t = t;
	hit->p = vadd(r->p, vmul(r->dir, hit->t));
	double height_proj = dot(vsub(hit->p, cylinder->pos), cylinder->axis);
	if (height_proj < -cylinder->height / 2 || height_proj > cylinder->height / 2)
	{
		double t_top = (cylinder->height / 2 - dot(oc, cylinder->axis)) / dot(r->dir, cylinder->axis);
		double t_bottom = (-cylinder->height / 2 - dot(oc, cylinder->axis)) / dot(r->dir, cylinder->axis);
		if (t_top > 0 && (t_top < hit->t || hit->t < 0))
		{
			t = t_top;
			hit->p = vadd(r->p, vmul(r->dir, t));
			if (magn(vsub(hit->p, vadd(cylinder->pos, vmul(cylinder->axis, cylinder->height / 2)))) <= cylinder->radius)
			{
				hit->t = t;
				hit->normal = cylinder->axis;
				hit->front = (dot(r->dir, hit->normal) < 0);
				hit->mat = &cylinder->mat;
				return (true);
			}
		}
		if (t_bottom > 0 && (t_bottom < hit->t || hit->t < 0))
		{
			t = t_bottom;
			hit->p = vadd(r->p, vmul(r->dir, t));
			if (magn(vsub(hit->p, vsub(cylinder->pos, vmul(cylinder->axis, cylinder->height / 2)))) <= cylinder->radius)
			{
				hit->t = t;
				hit->normal = vmul(cylinder->axis, -1);
				hit->front = (dot(r->dir, hit->normal) < 0);
				hit->mat = &cylinder->mat;
				return (true);
			}
		}
		return (false);
	}
	t_vec hit_to_center = vsub(hit->p, cylinder->pos);
	t_vec proj_axis = vmul(cylinder->axis, dot(hit_to_center, cylinder->axis));
	hit->normal = norm(vsub(hit_to_center, proj_axis));
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->mat = &cylinder->mat;
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	hit->v = (height_proj + cylinder->height / 2) / cylinder->height;
	return (true);
}
*/
