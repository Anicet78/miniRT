/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/11 15:53:22 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel_to_img(t_mlx *mlx, void *addr, uint32_t coords[2], int color)
{
	char			*dst;
	const int		x = coords[0];
	const int		y = coords[1];

	if (x > mlx->width || y > mlx->height)
		return ;
	dst = addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

bool	create_images(t_mlx *mlx, t_arena *arena, size_t img_amount)
{
	size_t	i;

	i = 0;
	mlx->img_amount = img_amount;
	mlx->imgs = arena_calloc(arena, sizeof(void *) * img_amount);
	mlx->addr = arena_calloc(arena, sizeof(void *) * img_amount);
	if (!mlx->imgs || !mlx->addr)
		return (false);
	while (i < img_amount)
	{
		mlx->imgs[i] = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
		if (!mlx->imgs[i])
			return (false);
		i++;
	}
	i = 0;
	while (i < img_amount)
	{
		mlx->addr[i] = mlx_get_data_addr(mlx->imgs[i], &mlx->bits_per_pixel,
				&mlx->line_length, &mlx->endian);
		if (!mlx->addr[i])
			return (false);
		i++;
	}
	return (true);
}

void	mlx_start(t_rt *rt, int width, int height)
{
	t_mlx	*mlx;

	mlx = &rt->mlx;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->mlx_win)
		kill_mlx(rt, EXIT_FAILURE);
	if (create_images(&rt->mlx, rt->arena, rt->elements.frame_amount) == false)
		kill_mlx(rt, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &destroy_hook, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &key_hook, mlx);
	mlx_loop_hook(mlx->mlx, &loop_hook, rt);
}
