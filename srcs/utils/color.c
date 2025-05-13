/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:31:23 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 13:23:16 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

	col = (uint32_t)(a.x * 255.999) << 16;
	col |= (uint32_t)(a.y * 255.999) << 8;
	col |= (uint32_t)(a.z * 255.999);
	return (col);
}

t_color	lerp_vec(t_color a, t_color b, double t)
{
	t_color	ret;

	ret.x = a.x + (b.x - a.x) * t;
	ret.y = a.y + (b.y - a.y) * t;
	ret.z = a.z + (b.z - a.z) * t;
	return (ret);
}
