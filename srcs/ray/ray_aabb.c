/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:24:46 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/17 01:06:22 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	swap_ts(double *t0, double *t1, bool is_neg)
{
	double	tmp;

	if (is_neg)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
}

static bool aabb_xyz(const double boxmin[3], const double boxmax[3],
	const double p[3], const double dir[3])
{
	int		i;
	double	tmin;
	double	tmax;
	double	t0;
	double	t1;

	tmin = -DBL_MAX;
	tmax = DBL_MAX;
	i = 0;
	while (i < 3)
	{
		if (dir[i] != 0.0)
		{
			t0 = (boxmin[i] - p[i]) / dir[i];
			t1 = (boxmax[i] - p[i]) / dir[i];
			swap_ts(&t0, &t1, dir[i] < 0);
			tmin = fmax(tmin, t0);
			tmax = fmin(tmax, t1);
			if (tmax > tmin)
				return (false);
		}
		else if (p[i] < boxmin[i] || p[i] > boxmax[i])
			return (false);
		i++;
	}
	if (tmax < 0)
		return (false);
	return (true);
}

bool	hit_aabb(t_aabb *box, t_ray *r)
{
	double	*boxmin;
	double	*boxmax;
	double	*p;
	double	*dir;

	boxmin = (double *)&box->min;
	boxmax = (double *)&box->max;
	p = (double *)&r->p;
	dir = (double *)&r->dir;
	return (aabb_xyz(boxmin, boxmax, p, dir));
}
