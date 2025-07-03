/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:21:01 by agruet            #+#    #+#             */
/*   Updated: 2025/06/17 17:00:20 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	print_pixels(t_block block, t_params *p, t_mlx *mlx)
{
	uint32_t			x;
	uint32_t			y;
	t_ray				r;
	t_point				world_pix;
	const t_elem_lst	elems = p->elements;
	const t_display		*d = &p->display[block.img_index];

	block.width += block.x_start;
	block.height += block.y_start;
	y = block.y_start;
	while (y < block.height)
	{
		x = block.x_start;
		while (x < block.width)
		{
			world_pix = vadd(d->pixel00,
					vadd(vmul(d->pix_du, x), vmul(d->pix_dv, y)));
			r.dir = norm(vsub(world_pix, elems.cam[block.img_index].pos));
			r.p = elems.cam[block.img_index].pos;
			put_pixel_to_img(mlx, mlx->addr[block.img_index], (uint32_t[2]){x, y},
				ray_to_color(&r, (t_elem_lst *)&elems, block.img_index));
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
			pthread_cond_signal(&params->queue->cond);
			return (NULL);
		}
		print_pixels(block, params, params->mlx);
		set_ready(params->queue, &block, params->mlx);
	}
	return (NULL);
}

double	wait_framerate(double fps, long last_frame_time)
{
	long		now;
	long		elapsed;
	double		duration;
	double		calc_fps;

	if (last_frame_time == 0)
	{
		last_frame_time = get_time_now();
		return (fps);
	}
	duration = 1000.0 / fps;
	now = get_time_now();
	elapsed = now - last_frame_time;
	if (elapsed < duration)
		ft_usleep((duration - elapsed) * 1000);
	elapsed = get_time_now() - last_frame_time;
	if (elapsed > 0)
		calc_fps = 1000.0 / (double)elapsed;
	else
		calc_fps = fps;
	return (calc_fps);
}

void	realtime_rendering(t_rt *rt, size_t *last_frame, long *last_frame_time)
{
	double	fps;

	fps = wait_framerate(rt->elements.fps, *last_frame_time);
	pthread_mutex_lock(&rt->queue.lock);
	if (rt->queue.print_index != 0 && *last_frame < rt->queue.print_index)
	{
		*last_frame = rt->queue.print_index;
		ft_printf("frame: %lu -> %.2ffps\n", *last_frame, fps);
		mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
			rt->mlx.imgs[(*last_frame) - 1], 0, 0);
		*last_frame_time = get_time_now();
	}
	pthread_mutex_unlock(&rt->queue.lock);
}

void	pre_rendering(t_rt *rt, long *last_frame_time)
{
	static size_t	count = 0;
	double			fps;

	fps = wait_framerate(rt->elements.fps, *last_frame_time);
	ft_printf("frame: %lu -> %.2ffps\n", count + 1, fps);
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
		rt->mlx.imgs[count++], 0, 0);
	if (count >= rt->elements.frame_amount)
		count = rt->elements.loop - 1;
	*last_frame_time = get_time_now();
}

void	next_image(t_rt *rt)
{
	static size_t	last_frame = 0;
	static long		last_frame_time = 0;
	double			fps;

	if (!rt->elements.loop && last_frame >= rt->elements.frame_amount)
		return ;
	else if (rt->elements.loop && last_frame >= rt->elements.frame_amount)
		pre_rendering(rt, &last_frame_time);
	else
		realtime_rendering(rt, &last_frame, &last_frame_time);
}

void	render_thread(t_rt *rt)
{
	rt->queue.counter = 0;
	rt->queue.render_index = 0;
	rt->elements.count = 0;
	pthread_mutex_unlock(&rt->queue.lock);
}
