/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:38:23 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/29 18:08:23 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

static bool	touch_cyl_body_part_two(
	t_cylinder *cyl, t_ray *r, t_hit *hit, t_vec hit_point)
{
	double	height;

	height = dot(vsub(hit_point, cyl->pos), cyl->axis);
	if (height < -cyl->h / 2 || height > cyl->h / 2)
		return (false);
	hit->p = hit_point;
	hit->normal = norm(vsub(hit_point,
				vadd(cyl->pos, vmul(cyl->axis, height))));
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->color = &cyl->color;
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	hit->v = (height + cyl->h / 2) / cyl->h;
	return (true);
}

bool	touch_cyl_body(t_cylinder *cyl, t_ray *r, t_hit *hit)
{
	const t_vec		oc = vsub(r->p, cyl->pos);
	const double	a = dot(r->dir, r->dir) - pow(dot(r->dir, cyl->axis), 2);
	const double	b = 2 * (dot(r->dir, oc)
			- dot(r->dir, cyl->axis) * dot(oc, cyl->axis));
	const double	c = dot(oc, oc)
		- pow(dot(oc, cyl->axis), 2) - pow(cyl->r, 2);
	const double	delta = b * b - 4 * a * c;

	if (delta < 0)
		return (false);
	auto double t = (-b - sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
		return (false);
	auto t_vec hit_point = vadd(r->p, vmul(r->dir, t));
	if (!touch_cyl_body_part_two(cyl, r, hit, hit_point))
		return (false);
	hit->t = t;
	return (true);
}

static bool	hit_cap(t_cylinder *cyl, t_ray *r,
	t_hit *hit, t_vec cap)
{
	const double	denom = dot(cyl->axis, r->dir);
	double			t;
	t_vec			point;

	if (fabs(denom) < 0.000001)
		return (false);
	t = dot(vsub(cap, r->p), cyl->axis) / denom;
	if (t < 0 || hit->t < t)
		return (false);
	point = vadd(r->p, vmul(r->dir, t));
	if (magn(vsub(point, cap)) > cyl->r)
		return (false);
	hit->p = point;
	hit->t = t;
	hit->normal = cyl->axis;
	hit->front = (denom < 0);
	if (!hit->front)
		hit->normal = vmul(hit->normal, -1);
	hit->color = &cyl->color;
	hit->u = fmod((hit->p.x - cap.x) / 2, 1);
	hit->v = fmod((hit->p.y - cap.y) / 2, 1);
	return (true);
}

bool	hit_cylinder(t_cylinder *cyl, t_ray *r, t_hit *hit)
{
	bool		did_hit;
	const t_vec	to_cap = vmul(cyl->axis, cyl->h / 2);

	did_hit = false;
	did_hit |= touch_cyl_body(cyl, r, hit);
	did_hit |= hit_cap(cyl, r, hit, vadd(cyl->pos, to_cap));
	did_hit |= hit_cap(cyl, r, hit, vsub(cyl->pos, to_cap));
	return (did_hit);
}
