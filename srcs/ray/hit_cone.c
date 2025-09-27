/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:31:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/09/24 15:49:45 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static bool	cone_math(t_cone *cone, const t_ray *r, t_cone_v *vs)
{
	const t_vec		oc = vsub(r->p, cone->pos);
	const double	k = pow(cone->radius / cone->height, 2);
	double			t1;
	t_vec			math;
	double			delta;

	math.x = dot(r->dir, r->dir) - (1 + k) * pow(dot(r->dir, cone->axis), 2);
	if (fabs(math.x) < 0.00000001)
		return (false);
	math.y = 2 * (dot(r->dir, oc) - (1 + k)
			* dot(r->dir, cone->axis) * dot(oc, cone->axis));
	math.z = dot(oc, oc) - (1 + k) * pow(dot(oc, cone->axis), 2);
	delta = math.y * math.y - 4 * math.x * math.z;
	if (delta < 0)
		return (false);
	vs->t = (-math.y - sqrt(delta)) / (2 * math.x);
	t1 = (-math.y + sqrt(delta)) / (2 * math.x);
	if (vs->t > t1 && t1 > 0)
		vs->t = t1;
	if (vs->t <= 0)
		return (false);
	vs->p = vadd(r->p, vmul(r->dir, vs->t));
	vs->tip_to_p = vsub(vs->p, cone->pos);
	vs->h = dot(vs->tip_to_p, cone->axis);
	return (vs->h > 0 && vs->h < cone->height);
}

static bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit *hit)
{
	double		hyp;
	double		cos_t;
	double		sin_t;
	t_vec		perp;
	t_cone_v	vs;

	if (!cone_math(cone, r, &vs))
		return (false);
	hit->t = vs.t;
	hit->p = vs.p;
	hyp = sqrt(pow(cone->radius, 2) + pow(cone->height, 2));
	cos_t = cone->radius / hyp;
	sin_t = cone->height / hyp;
	perp = norm(vsub(vs.tip_to_p, vmul(cone->axis, vs.h)));
	hit->normal = norm(vsub(vmul(perp, cos_t), vmul(cone->axis, sin_t)));
	hit->mat = &cone->mat;
	return (true);
}

bool	hit_cone(t_cone *cone, t_ray *r, t_hit *hit)
{
	bool	did_hit;

	did_hit = false;
	did_hit |= hit_cone_body(cone, r, hit);
	did_hit |= hit_cap(
			cone,
			r,
			hit,
			vadd(cone->pos, vmul(cone->axis, cone->height))
			);
	return (did_hit);
}
