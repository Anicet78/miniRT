/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:31:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/25 22:03:58 by tgallet          ###   ########.fr       */
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

static bool cone_math(t_cone *cone, const t_ray *r, double *t0, double *t1)
{
	const t_vec		oc = vsub(r->p, cone->pos);
	const double	k = pow(cone->radius / cone->height, 2);
	t_vec			math;
	double			delta;

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
	return (t0 < 0);
}

bool	hit_cone(t_cone *cone, t_ray *r, t_hit *hit)
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
		vmul(cone->axis, dot(center_to_hit, cone->axis) / dot(cone->axis, cone->axis))));
	hit->u = 0.5 + atan2(center_to_hit.z, center_to_hit.x) / (2 * PI);
	hit->v = dot(center_to_hit, cone->axis) / cone->height;
	hit->front = (dot(r->dir, hit->normal) < 0);
	hit->mat = &cone->mat;
	return (true);
}
