/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:21:01 by agruet            #+#    #+#             */
/*   Updated: 2025/09/09 18:10:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static void	print_pixels(t_block block, t_params *p)
{
	uint32_t			x;
	uint32_t			y;

	y = block.y_start;
	block.width += block.x_start;
	block.height += block.y_start;
	while (y < block.height)
	{
		x = block.x_start;
		while (x < block.width)
		{
			create_rays(&p->display[block.img_index],
				(uint32_t[2]){x, y}, block.img_index, p);
			x++;
		}
		y++;
	}
}

void	*start_routine(void *param)
{
	t_block		block;
	t_params	*params;

	params = param;
	while (true)
	{
		if (!get_next_block(&block, params->queue, &params->elements))
		{
			clear_arena(&params->arena);
			return (NULL);
		}
		print_pixels(block, params);
		set_ready(params->queue, &block);
	}
	return (NULL);
}

void	realtime_rendering(t_rt *rt, size_t *last_frame, long *last_frame_time)
{
	double	fps;

	fps = wait_framerate(rt->elements.fps, *last_frame_time);
	pthread_mutex_lock(&rt->queue.lock);
	if (rt->queue.print_index != 0 && *last_frame < rt->queue.print_index)
	{
		(*last_frame)++;
		mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
			rt->mlx.imgs[(*last_frame) - 1], 0, 0);
		print_fps(&rt->mlx, fps);
		*last_frame_time = get_utime_now();
	}
	pthread_mutex_unlock(&rt->queue.lock);
}

void	pre_rendering(t_rt *rt, long *last_frame_time)
{
	static size_t	count = SIZE_MAX;
	double			fps;

	if (count == SIZE_MAX)
		count = rt->elements.loop - 1;
	fps = wait_framerate(rt->elements.fps, *last_frame_time);
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
		rt->mlx.imgs[count++], 0, 0);
	print_fps(&rt->mlx, fps);
	*last_frame_time = get_utime_now();
	if (count >= rt->elements.frame_amount)
		count = rt->elements.loop - 1;
}

void	render_thread(t_rt *rt)
{
	rt->queue.counter = 0;
	rt->queue.render_index = 0;
	rt->elements.count = 0;
	pthread_mutex_unlock(&rt->queue.lock);
}
