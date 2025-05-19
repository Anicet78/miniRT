/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:38:23 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/17 23:57:16 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_cyl_body_part_two(
	t_cylinder *cyl, t_ray *r, t_hit *hit, t_vec hit_point)
{
	double	height;

	height = dot(vsub(hit_point, cyl->pos), cyl->axis);
	if (height < -cyl->height / 2 || height > cyl->height / 2)
		return (false);
	hit->p = hit_point;
	hit->normal = norm(vsub(hit_point, vadd(cyl->pos, vmul(cyl->axis, height))));
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->mat = &cyl->mat;
	hit->u = atan2(hit->normal.z, hit->normal.x) / (2 * PI);
	hit->v = (height + cyl->height / 2) / cyl->height;
	return (true);
}

bool intersect_cyl_body(t_cylinder *cyl, t_ray *r, t_hit *hit)
{
	const t_vec		oc = vsub(r->p, cyl->pos);
	const double	a = dot(r->dir, r->dir) - pow(dot(r->dir, cyl->axis), 2);
	const double	b = 2 * (dot(r->dir, oc)
						- dot(r->dir, cyl->axis) * dot(oc, cyl->axis));
	const double	c = dot(oc, oc)
						- pow(dot(oc, cyl->axis), 2) - pow(cyl->radius, 2);
	const double	delta = b * b - 4 * a * c;
	double 			t;
	t_vec			hit_point;

	if (delta < 0)
		return (false);
	t = (-b - sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
		return (false);
	hit_point = vadd(r->p, vmul(r->dir, t));
	if (!intersect_cyl_body_part_two(cyl, r, hit, hit_point))
		return (false);
	hit->t = t;
	return (true);
}

bool intersect_cyl_caps(t_cylinder *cylinder, t_ray *r, t_hit *hit, t_vec cap_center)
{
	const double	denom = dot(cylinder->axis, r->dir);
	double			t;
	t_vec			point;

	if (fabs(denom) < 0.000001)
		return (false);
	t = dot(vsub(cap_center, r->p), cylinder->axis) / denom;
	if (t < 0 || hit->t < t)
		return (false);
	point = vadd(r->p, vmul(r->dir, t));
	if (magn(vsub(point, cap_center)) > cylinder->radius)
		return (false);
	hit->p = point;
	hit->t = t;
	hit->normal = cylinder->axis;
	hit->front = (denom < 0);
	hit->mat = &cylinder->mat;
	hit->u = fmod(hit->p.x - cap_center.x, 4);
	hit->v = fmod(hit->p.y - cap_center.y, 4);
	return (true);
}

bool hit_cylinder(t_cylinder *cylinder, t_ray *r, t_hit *hit)
{
	if (intersect_cyl_body(cylinder, r, hit)
		|| intersect_cyl_caps(cylinder, r, hit,
			vadd(cylinder->pos, vmul(cylinder->axis, cylinder->height / 2)))
		|| intersect_cyl_caps(cylinder, r, hit,
			vsub(cylinder->pos, vmul(cylinder->axis, cylinder->height / 2))))
		return (true);
}
