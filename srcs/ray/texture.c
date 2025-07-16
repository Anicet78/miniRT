/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:17:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/16 17:11:05 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

uint32_t	get_pixel_from_img(t_image *data, int x, int y)
{
	return (*(uint32_t *)(data->addr + y * data->line_length
		+ x * data->bits_per_pixel / 8));
}

t_color	surface_color(t_image *texture, double u, double v)
{
	int			x;
	int			y;
	uint32_t	col;

	if (!texture || texture->width <= 0 || texture->height <= 0)
		return ((t_color){{1.0, 1.0, 1.0}});
	u = fmin(fmax(u, 0), 1);
	v = fmin(fmax(v, 0), 1);
	x = (int)(u * texture->width) % texture->width;
	y = (int)(v * texture->height) % texture->height;
	col = get_pixel_from_img(texture, x, y);
	return (int_to_tcol(col));
}
