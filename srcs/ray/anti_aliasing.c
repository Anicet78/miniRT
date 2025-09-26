/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:19 by agruet            #+#    #+#             */
/*   Updated: 2025/09/26 19:53:15 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static inline
double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

static
t_vec	sample_square(void)
{
	return ((t_vec){{random_double() - 0.5, random_double() - 0.5, 0}});
}

static inline
t_vec	get_world_pix(const t_display *d, uint32_t x, uint32_t y)
{
	const t_vec	offset = sample_square();

	return (vadd(d->pixel00,
			vadd(vmul(d->pix_du, offset.x + (double)x),
				vmul(d->pix_dv, offset.y + (double)y))));
}

static
t_ray	get_ray(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_point				world_pix;
	t_ray				r;
	const uint32_t		x = coords[0];
	const uint32_t		y = coords[1];

	if (p->elements.aliasing == 1)
		world_pix = vadd(d->pixel00, vadd(vmul(d->pix_du, x),
					vmul(d->pix_dv, y)));
	else
		world_pix = get_world_pix(d, x, y);
	r.dir = norm(vsub(world_pix, p->elements.cam[img_index].pos));
	r.p = p->elements.cam[img_index].pos;
	return (r);
}

bool	is_col_far(t_color col1, t_color col2)
{
	col1 = vsub(col1, col2);
	return (dot(col1, col2) < 0.0025f);
}

bool	aa_early_exit(t_color diff[AA_EARLY_EXIT])
{
	uint64_t	i;

	if (AA_EARLY_EXIT <= 1)
		return (true);
	i = 0;
	while (i < (uint64_t)(AA_EARLY_EXIT - 1))
	{
		if (is_col_far(diff[i], diff[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

void	create_rays(const t_display *d, uint32_t coords[2],
	size_t img_index, t_params *p)
{
	t_color			pixel_color;
	uint64_t		sample;
	t_ray			r;
	static double	ratio = 0;
	t_color			diff[AA_EARLY_EXIT];

	if (ratio == 0)
		ratio = 1.0 / (double)p->elements.aliasing;
	pixel_color = (t_vec){{0, 0, 0}};
	sample = 0;
	while (sample < p->elements.aliasing)
	{
		r = get_ray(d, coords, img_index, p);
		if (sample < AA_EARLY_EXIT)
		{
			diff[sample] = ray_to_color(&r, &p->elements, img_index);
			pixel_color = vadd(pixel_color, diff[sample]);
		}
		else if (sample == AA_EARLY_EXIT && aa_early_exit(diff))
		{
			printf("early exit\n");
			put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
				vec_to_col(vdiv(pixel_color, AA_EARLY_EXIT)));
			return ;
		}
		else
			pixel_color = vadd(pixel_color,
				ray_to_color(&r, &p->elements, img_index));
		sample++;
	}
	put_pixel_to_img(p->mlx, p->mlx->addr[img_index], coords,
		vec_to_col(vmul(pixel_color, ratio)));
}
