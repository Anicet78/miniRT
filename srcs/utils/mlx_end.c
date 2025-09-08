/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:36:08 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:14:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

void	destroy_mlx(t_rt *rt)
{
	size_t	i;

	i = 0;
	while (rt->elements.textures && i < rt->elements.texture_amount
		&& rt->elements.textures[i].declared)
		mlx_destroy_image(rt->mlx.mlx, rt->elements.textures[i++].img);
	i = 0;
	while (rt->elements.bmaps && i < rt->elements.bmaps_amount
		&& rt->elements.bmaps[i].declared)
		mlx_destroy_image(rt->mlx.mlx, rt->elements.bmaps[i++].img);
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
