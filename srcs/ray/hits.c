/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:57:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/16 17:10:56 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	if (t < 0)
		t = (-b + sqrt(delta)) / (2 * a);
	if (t < 0 || hit->t < t)
		return (false);
	hit->t = t;
	hit->p = vadd(r->p, vmul(r->dir, hit->t));
	hit->normal = norm(vsub(hit->p, sphere->pos));
	hit->mat = &sphere->mat;
	hit->front = (dot(r->dir, hit->normal) < 0);
	if (!hit->front)
		hit->normal = vmul(hit->normal, -1);
	hit->u = 0.5 - (atan2(hit->normal.z, hit->normal.x) / (2 * PI));
	hit->v = 0.5 - (asin(hit->normal.y) / PI);
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
	if (!hit->front)
		hit->normal = vmul(hit->normal, -1);
	return (true);
}
