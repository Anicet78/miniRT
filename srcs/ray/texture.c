/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:17:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/06 17:18:36 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


uint32_t	get_pixel_from_img(t_tpmp *data, int x, int y)
{
	return (*(uint32_t *)(data->addr + y * data->line_size
		+ x * data->bpp / 8));
}

// TODO: adapter à ta structure d'img
t_color	surface_color(t_tpmp *texture, double u, double v)
{
	int			x;
	int			y;
	uint32_t	col;

	if (!texture || texture->width <= 0 || texture->height <= 0)
		return ((t_color){1.0, 1.0, 1.0});
	u = mind(maxd(u, 0), 1);
	v = mind(maxd(v, 0), 1);
	x = (int)(u * texture->width) % texture->width;
	y = (int)(v * texture->height) % texture->height;
	col = get_pixel_from_img(texture, x, y);
	return (int_to_tcol(col));
}

