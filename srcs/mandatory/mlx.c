/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:41:26 by agruet            #+#    #+#             */
/*   Updated: 2025/09/09 19:10:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mandatory.h"

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > mlx->width || y < 0 || y > mlx->height)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	kill_mlx(t_rt *rt, int exit_code)
{
	if (rt->mlx.img)
		mlx_destroy_image(rt->mlx.mlx, rt->mlx.img);
	if (rt->mlx.mlx_win)
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.mlx_win);
	if (rt->mlx.mlx)
	{
		mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
	}
	if (rt->arena)
		clear_arena(&rt->arena);
	exit(exit_code);
}

static int	destroy_hook(t_rt *rt)
{
	kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}

static int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == ESC_K)
		kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}

void	mlx_start(t_rt *rt, int width, int height)
{
	t_mlx	*mlx;

	mlx = &rt->mlx;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		kill_mlx(rt, EXIT_FAILURE);
	rt->elements.mlx_ptr = mlx->mlx;
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "mimiRT");
	if (!mlx->mlx_win)
		kill_mlx(rt, EXIT_FAILURE);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (!mlx->img)
		kill_mlx(rt, EXIT_FAILURE);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		kill_mlx(rt, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &destroy_hook, rt);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &key_hook, rt);
}
