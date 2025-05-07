/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:20 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/07 16:29:08 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	hit_sphere(t_point center, double radius, t_ray r)
{
	t_vec	oc;

	oc = vsub(center, r.p);
	
}

void	test_display(t_display display, t_mlx *mlx, t_elem_lst *elements)
{
	const float	focal_lenght = display.focal_len;
	const t_vec	camera_center = elements->cam.pos;
	const t_vec	viewport_u = (t_vec){display.vp_width, 0, 0};
	const t_vec	viewport_v = (t_vec){0, -display.vp_height, 0};
	const t_vec	pixel_delta_u = vdiv(viewport_u, display.width);
	const t_vec	pixel_delta_v = vdiv(viewport_v, display.height);
	const t_vec	viewport_upper_left = vsub(vsub(camera_center,
				(t_vec){0, 0, focal_lenght}), vsub(vdiv(viewport_u, 2),
				vdiv(viewport_v, 2)));
	const t_vec	pixel00_loc = vadd(vmul(viewport_upper_left, 0.5),
			vadd(pixel_delta_u, pixel_delta_v));
	int			j = 0;
	int			i;

	while (j < display.height)
	{
		i = 0;
		while (i < display.width)
		{
			t_vec	pixel_center = vadd(vadd(pixel00_loc,
				vmul(pixel_delta_u, i)), vmul(pixel_delta_v, j));
			t_vec	ray_direction = vsub(pixel_center, camera_center);
			t_ray	r = {camera_center, ray_direction};
			t_color pixel_color = ray_color(&r);
			put_pixel_to_img(mlx, i, j, vec_to_intcol(pixel_color));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}



