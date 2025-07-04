/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:50:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/03 17:15:50 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	normal_map(t_image *texture, double u, double v)
{
	int			x;
	int			y;
	uint32_t	pix;
	t_vec		ret;

	if (!texture)
		return ((t_vec){0, 0, -1.0});
	x = (int)(u * texture->width) % texture->width;
	y = (int)(v * texture->height) % texture->height;
	pix = get_pixel_from_img(texture, x, y);
	ret.x = ((pix >> 16) & 0xFF) / 127.99 - 1;
	ret.y = ((pix >> 8) & 0xFF) / 127.99 - 1;
	ret.z = (pix & 0xFF) / -127.99 + 1;
	ret.z = maxf(ret.z, 0);
	return (ret);
}