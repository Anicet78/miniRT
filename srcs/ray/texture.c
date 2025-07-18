/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:17:32 by tgallet           #+#    #+#             */
/*   Updated: 2025/07/18 23:31:07 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

uint32_t	get_pixel_img(t_image *data, int x, int y)
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
	x = (int)(u * texture->width);
	y = (int)(v * texture->height);
	col = get_pixel_img(texture, x, y);
	return (int_to_tcol(col));
}

int	get_grey_pixel(t_image *data, int x, int y)
{
	return (((*(uint32_t *)(data->addr + y * data->line_length
		+ x * data->bits_per_pixel / 8)) & 0xFF00) >> 8);
}

t_vec	bump_gradient(t_image *bmap, double u, double v)
{
	const int	x = ((uint32_t)(u * bmap->width)) % bmap->width;
	const int	y = ((uint32_t)(v * bmap->height)) % bmap->height;
	t_vec	ret;

	ret.x = get_grey_pixel(bmap, (x - 1) % bmap->width, y)
			- get_grey_pixel(bmap, (x + 1) % bmap->width, y);
	ret.y = get_grey_pixel(bmap, x, (y - 1) % bmap->height)
			- get_grey_pixel(bmap, x, (y + 1) % bmap->height);
	ret = vmul(ret, 1 / 510);
	return (ret);
}

void	bump_mapping(t_hit *hit)
{
	const t_vec	tang = norm(cross_prod(hit->normal, up_v()));
	const t_vec	bitang = cross_prod(tang, hit->normal);
	const t_vec	grad = bump_gradient(hit->mat->bmap, hit->u, hit->v);

	hit->normal = norm(
		vsub(
			hit->normal,
			vmul(
				vadd(
					vmul(tang, grad.x),
					vmul(bitang, grad.y)
					),
				BUMP_POWER
				)
			)
		);
}
