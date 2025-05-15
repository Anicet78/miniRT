/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:43 by agruet            #+#    #+#             */
/*   Updated: 2025/05/15 15:13:14 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	destroy_hook(t_rt *rt)
{
	kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == ESC_K)
		kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}

void	put_pixel_to_img(t_mlx *mlx, void *addr, uint32_t coords[2], int color)
{
	char		*dst;
	const int	x = coords[0];
	const int	y = coords[1];

	if (x < 0 || x > mlx->width || y < 0 || y > mlx->height)
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

	rt->thread_amount = 0;
	mlx = &rt->mlx;
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->imgs = NULL;
	mlx->addr = NULL;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		kill_mlx(rt, EXIT_FAILURE);
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->mlx_win)
		kill_mlx(rt, EXIT_FAILURE);
	if (create_images(&rt->mlx, rt->arena, rt->elements.frame_amount) == false)
		kill_mlx(rt, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &destroy_hook, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &key_hook, mlx);
}

void	destroy_mlx(t_rt *rt)
{
	size_t	i;

	i = 0;
	while (i < rt->mlx.img_amount && rt->mlx.imgs[i])
	{
		mlx_destroy_image(rt->mlx.mlx, rt->mlx.imgs[i]);
		i++;
	}
	if (rt->mlx.mlx_win)
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.mlx_win);
	if (rt->mlx.mlx)
	{
		mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
	}
}

void	destroy_threads(t_rt *rt)
{
	uint8_t	i;

	i = 0;
	pthread_mutex_unlock(&rt->queue.lock);
	while (i < rt->thread_amount)
	{
		pthread_join(rt->threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&rt->queue.lock);
	pthread_cond_destroy(&rt->queue.cond);
}

void	kill_mlx(t_rt *rt, int exit_code)
{
	if (rt->thread_amount != 0)
		destroy_threads(rt);
	destroy_mlx(rt);
	if (rt->arena)
		clear_arena(&rt->arena);
	exit(exit_code);
}
