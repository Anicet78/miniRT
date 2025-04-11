/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:33:36 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/10 18:03:58 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

// xyz becomes rgb
uint32_t	vec_to_intcol(t_color a)
{
	uint32_t	col;

	col = (uint32_t)(a.x * 255.999) << 16;
	col |= (uint32_t)(a.y * 255.999) << 8;
	col |= (uint32_t)(a.z * 255.999);
	return (col);
}
