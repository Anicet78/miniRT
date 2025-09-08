/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:31:23 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 18:03:57 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t	hex;

	hex = r;
	hex <<= 8;
	hex += g;
	hex <<= 8;
	hex += b;
	return (hex);
}

uint32_t	vec_to_col(t_color a)
{
	uint32_t	col;

	a.x = fmax(fmin(1, a.x), 0);
	a.y = fmax(fmin(1, a.y), 0);
	a.z = fmax(fmin(1, a.z), 0);
	col = (uint32_t)(a.x * 255.999) << 16;
	col |= (uint32_t)(a.y * 255.999) << 8;
	col |= (uint32_t)(a.z * 255.999);
	return (col);
}

t_color	int_to_tcol(uint32_t col)
{
	t_color	a;

	a.x = ((col >> 16) & 0xFF) / 255.999;
	a.y = ((col >> 8) & 0xFF) / 255.999;
	a.z = (col & 0xFF) / 255.999;
	return (a);
}

t_color	lerp_vec(t_color a, t_color b, double t)
{
	t_color	ret;

	ret.x = a.x + (b.x - a.x) * t;
	ret.y = a.y + (b.y - a.y) * t;
	ret.z = a.z + (b.z - a.z) * t;
	return (ret);
}
