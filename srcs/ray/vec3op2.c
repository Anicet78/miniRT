/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:33:36 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/06 17:53:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vsub(t_vec a, t_vec b)
{
	a.x += -b.x;
	a.y += -b.y;
	a.z += -b.z;
	return (a);
}

t_vec	vdiv(t_vec a, double scalar)
{
	a.x /= scalar;
	a.y /= scalar;
	a.z /= scalar;
	return (a);
}

t_vec	vtrans(t_vec a, double scalar)
{
	a.x += scalar;
	a.y += scalar;
	a.z += scalar;
	return (a);
}

t_vec	cross_prod(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec	hadamar(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}
