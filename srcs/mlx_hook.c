/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:13:00 by agruet            #+#    #+#             */
/*   Updated: 2025/06/05 12:16:30 by agruet           ###   ########.fr       */
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
	else if (keycode == SPACE_K)
	{
		pthread_mutex_lock(&rt->queue.lock);
		reset_ready(&rt->queue, &rt->elements, 0);
		render_thread(rt);
	}
	return (0);
}

int	loop_hook(t_rt *rt)
{
	static bool		first = true;
	static size_t	index;

	if (first == true)
	{
		first = false;
		render_thread(rt);
		return (0);
	}
	wait_image(rt);
	return (0);
}

void	destroy_mlx(t_rt *rt)
{
	size_t	i;

	i = 0;
	while (rt->elements.textures && i < rt->elements.texture_amount
		&& rt->elements.textures[i].declared)
		mlx_destroy_image(rt->mlx.mlx, rt->elements.textures[i++].img);
	i = 0;
	while (rt->elements.normals && i < rt->elements.normal_amount
		&& rt->elements.normals[i].declared)
		mlx_destroy_image(rt->mlx.mlx, rt->elements.normals[i++].img);
	i = 0;
	while (rt->mlx.mlx && rt->mlx.mlx_win
		&& i < rt->mlx.img_amount && rt->mlx.imgs[i])
		mlx_destroy_image(rt->mlx.mlx, rt->mlx.imgs[i++]);
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
	pthread_mutex_lock(&rt->queue.lock);
	rt->queue.stop = true;
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
