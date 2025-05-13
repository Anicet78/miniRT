/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:57:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/13 19:21:37 by tgallet          ###   ########.fr       */
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
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	hit->v = atan2(hit->normal.y, sqrt(hit->normal.x * hit->normal.x
				+ hit->normal.z * hit->normal.z)) / PI;
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

bool	hit_cylinder(t_cylinder *c, t_ray *r, t_hit *hit)
{
	const t_vec		oc = vsub(r->p, c->pos);
	const double	a = dot(r->dir, r->dir) - pow(dot(r->dir, c->axis), 2);
	const double	b = 2 * (dot(r->dir, oc) - dot(r->dir, c->axis) * dot(oc, c->axis));
	const double	c_val = dot(oc, oc) - pow(dot(oc, c->axis), 2) - pow(c->radius, 2);
	const double	delta = b * b - 4 * a * c_val;
	double			t;
	const double 	height_check = dot(vsub(hit->p, c->pos), c->axis);


	if (height_check < 0 || height_check > c->height)
		return (false);
	if (delta < 0)
		return (false);
	t = (-b - sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
		return (false);
	hit->t = t;
	hit->p = vadd(r->p, vmul(r->dir, t));
	hit->normal = norm(vsub(vsub(hit->p, c->pos),
		vmul(c->axis, dot(vsub(hit->p, c->pos), c->axis))));
	hit->front = (dot(r->dir, hit->normal) < 0);
	if (!hit->front)
		hit->normal = vmul(hit->normal, -1);
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	hit->v = dot(vsub(hit->p, c->pos), c->axis) / c->height;
	hit->mat = &c->mat;
	return (true);
}
