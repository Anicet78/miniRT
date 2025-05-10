/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:44:34 by agruet            #+#    #+#             */
/*   Updated: 2025/05/07 16:47:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool hit_sphere(t_point center, double radius, t_ray r) {
	t_vec	oc = vsub(center, r.p);
	double	a = dot(r.dir, r.dir);
	double	b = -2.0 * dot(r.dir, oc);
	double	c = dot(oc, oc) - radius * radius;
	double	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

t_color	ray_color(t_ray *r)
{
	if (hit_sphere((t_point){0, 0, 0}, 1, *r))
	{
		// ft_printf("aaaaaaaaaaaaaaaa\n");
		return ((t_color){1, 0, 0});
	}
	double	a = 0.5 * (r->dir.y + 1.0);
	return (vadd(vmul((t_color){1.0, 1.0, 1.0}, 1.0 - a), vmul((t_color){0.5, 0.7, 1.0}, a)));
}
