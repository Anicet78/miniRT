/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:31:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/22 21:54:04 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void swap(double *a, double *b)
{
	double	temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

static bool cone_math(t_cone *cone, const t_ray *r, double *t0, double *t1)
{
	const t_vec		oc = vsub(r->p, cone->pos);
	const double	k = pow(cone->radius / cone->height, 2);
	const double	a = dot(r->dir, r->dir) - (1 + k) * pow(dot(r->dir, cone->axis), 2);
	const double	b = 2 * (
						dot(r->dir, oc) - (1 + k)
						* dot(r->dir, cone->axis)
						* dot(oc, cone->axis)
					);
	const double	c = dot(oc, oc) - (1 + k) * pow(dot(oc, cone->axis), 2);
	const double	delta = b * b - 4 * a * c;

	if (delta < 0)
		return (false);
	*t0 = (-b - sqrt(delta)) / (2 * a);
	*t1 = (-b + sqrt(delta)) / (2 * a);
	if (*t0 > *t1 && *t1 > 0)
		swap(t0, t1);
	return (true);
}

bool	hit_cone(t_cone *cone, t_ray *r, t_hit *hit)
{
	double		t0;
	double		t1;
	t_vec		center_to_hit;

	if (!cone_math(cone, r, &t0, &t1))
		return (false);
	if (t0 < 0)
		return (false);
	hit->t = t0;
	hit->p = vadd(r->p, vmul(r->dir, t0));
	center_to_hit = vsub(hit->p, cone->pos);
	hit->normal = norm(vsub(center_to_hit,
		vmul(cone->axis, dot(center_to_hit, cone->axis) / dot(cone->axis, cone->axis))));
	hit->u = 0.5 + atan2(center_to_hit.z, center_to_hit.x) / (2 * PI);
	hit->v = dot(center_to_hit, cone->axis) / cone->height;
	hit->front = (dot(r->dir, hit->normal) < 0);
	return (true);
}
