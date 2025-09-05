/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:31:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/05 16:04:22 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	swap(double *a, double *b)
{
	double	temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

static bool	hit_cone_caps(t_cone *cone, t_ray *r,
	t_hit *hit, t_vec cap_center)
{
	const double	denom = dot(cone->axis, r->dir);
	double			t;
	t_vec			point;

	if (fabs(denom) < 0.000001)
		return (false);
	t = dot(vsub(cap_center, r->p), cone->axis) / denom;
	if (t < 0 || hit->t < t)
		return (false);
	point = vadd(r->p, vmul(r->dir, t));
	if (magn(vsub(point, cap_center)) > cone->radius)
		return (false);
	hit->p = point;
	hit->t = t;
	hit->normal = cone->axis;
	hit->front = (denom < 0);
	hit->mat = &cone->mat;
	hit->u = fmod((hit->p.x - cap_center.x) / 2, 1);
	hit->v = fmod((hit->p.y - cap_center.y) / 2, 1);
	return (true);
}


static bool cone_math(t_cone *cone, const t_ray *r, double *t0, double *t1)
{
	const t_vec		oc = vsub(r->p, cone->pos);
	const double	k = pow(cone->radius / cone->height, 2);
	t_vec			math;
	double			delta;
	double			idk;

	math.x = dot(r->dir, r->dir) - (1 + k) * pow(dot(r->dir, cone->axis), 2);
	math.y = 2 * (dot(r->dir, oc) - (1 + k)
				* dot(r->dir, cone->axis)
				* dot(oc, cone->axis));
	math.z = dot(oc, oc) - (1 + k) * pow(dot(oc, cone->axis), 2);
	delta = math.y * math.y - 4 * math.x * math.z;
	if (delta < 0)
		return (false);
	*t0 = (-math.y - sqrt(delta)) / (2 * math.x);
	*t1 = (-math.y + sqrt(delta)) / (2 * math.x);
	if (*t0 > *t1 && *t1 > 0)
		swap(t0, t1);
	idk = dot(vsub(vadd(r->p, vmul(r->dir, *t0)), cone->pos), cone->axis);
	return (*t0 > 0 && idk > 0 && idk < cone->height);
}

static bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit *hit)
{
	double		t0;
	double		t1;
	t_vec		center_to_hit;

	if (!cone_math(cone, r, &t0, &t1))
		return (false);
	hit->t = t0;
	hit->p = vadd(r->p, vmul(r->dir, t0));
	center_to_hit = vsub(hit->p, cone->pos);
	hit->normal = norm(vsub(center_to_hit,
		vmul(cone->axis,
		dot(center_to_hit, cone->axis) / dot(cone->axis, cone->axis))));
	hit->u = 0.5 + atan2(center_to_hit.z, center_to_hit.x) / (2 * PI);
	hit->v = dot(center_to_hit, cone->axis) / cone->height;
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->mat = &cone->mat;
	return (true);
}

bool	hit_cone(t_cone *cone, t_ray *r, t_hit *hit)
{
	bool	did_hit;

	did_hit = false;
	did_hit |= hit_cone_body(cone, r, hit);
	did_hit |= hit_cone_caps(
				cone,
				r,
				hit,
				vadd(cone->pos, vmul(cone->axis, cone->height))
			);
	return (did_hit);
}
