/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:13:00 by agruet            #+#    #+#             */
/*   Updated: 2025/07/16 17:14:32 by agruet           ###   ########.fr       */
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
	{
		write(1, "\n", 1);
		kill_mlx(rt, EXIT_SUCCESS);
	}
	return (0);
}

void	next_image(t_rt *rt)
{
	static size_t	last_frame = 0;
	static long		last_frame_time = 0;

	if (!rt->elements.loop && last_frame >= rt->elements.frame_amount)
		return ;
	else if (rt->elements.loop && last_frame >= rt->elements.frame_amount)
		pre_rendering(rt, &last_frame_time);
	else
		realtime_rendering(rt, &last_frame, &last_frame_time);
}

int	loop_hook(t_rt *rt)
{
	static bool	first = true;

	if (first == true)
	{
		first = false;
		render_thread(rt);
		return (0);
	}
	next_image(rt);
	return (0);
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
