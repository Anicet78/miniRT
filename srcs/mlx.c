/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:43 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 19:21:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	destroy_hook(t_rt *minirt)
{
	kill_mlx(minirt, EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_rt *minirt)
{
	if (keycode == ESC_K)
		kill_mlx(minirt, EXIT_SUCCESS);
	return (0);
}

void	put_pixel_to_img(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_start(t_rt *minirt, int width, int height)
{
	t_mlx	*mlx;

	mlx = &minirt->mlx;
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		kill_mlx(minirt, EXIT_FAILURE);
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->mlx_win)
		kill_mlx(minirt, EXIT_FAILURE);
	mlx->img = mlx_new_image(mlx->mlx, width, height);
	if (!mlx->img)
		kill_mlx(minirt, EXIT_FAILURE);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		kill_mlx(minirt, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &destroy_hook, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &key_hook, mlx);
}

void	kill_mlx(t_rt *minirt, int exit_code)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&minirt->queue.lock);
	pthread_cond_broadcast(&minirt->queue.cond);
	while (i < minirt->thread_amount)
		pthread_join(minirt->threads[i++], NULL);
	if (minirt->arena)
		clear_arena(&minirt->arena);
	if (minirt->mlx.img)
		mlx_destroy_image(minirt->mlx.mlx, minirt->mlx.img);
	if (minirt->mlx.mlx_win)
		mlx_destroy_window(minirt->mlx.mlx, minirt->mlx.mlx_win);
	if (minirt->mlx.mlx)
	{
		mlx_destroy_display(minirt->mlx.mlx);
		free(minirt->mlx.mlx);
	}
	exit(exit_code);
}
