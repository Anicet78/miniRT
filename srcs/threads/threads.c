/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:52:58 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 19:22:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	print_pixels(t_block block, t_mlx *img, t_display *d, t_elem_lst *elements)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		r;
	t_point		world_pix;

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
			r.dir = norm(vsub(world_pix, elements->cam.pos));
			r.p = elements->cam.pos;
			put_pixel_to_img(img, x, y, ray_to_color(&r, elements));
			x++;
		}
		y++;
	}
}

void	*start_routine(void *param)
{
	t_block		*block_ptr;
	t_params	*params;

	params = param;
	while (true)
	{
		block_ptr = get_next_block(params->queue);
		if (!block_ptr)
		{
			pthread_mutex_lock(&params->queue->lock);
			pthread_cond_wait(&params->queue->cond, &params->queue->lock);
			if (params->queue->counter >= params->queue->size)
			{
				pthread_mutex_unlock(&params->queue->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&params->queue->lock);
			continue ;
		}
		print_pixels(*block_ptr, params->img, params->display, params->elements);
		set_ready(params->queue);
	}
	return (NULL);
}

static bool	init_mutex(t_queue *queue)
{
	if (pthread_mutex_init(&queue->lock, NULL))
		return (false);
	if (pthread_cond_init(&queue->cond, NULL))
	{
		pthread_mutex_destroy(&queue->lock);
		return (false);
	}
	return (true);
}

bool	init_threads(t_rt *minirt, t_display *display)
{
	t_params	*params;

	minirt->thread_amount = 0;
	if (init_mutex(&minirt->queue) == false)
		return (false);
	minirt->threads = arena_alloc(sizeof(pthread_t) * RENDER_THREADS, minirt->arena);
	if (!minirt->threads)
		return (false);
	pthread_mutex_lock(&minirt->queue.lock);
	while (minirt->thread_amount < RENDER_THREADS)
	{
		params = arena_alloc(sizeof(t_params), minirt->arena);
		if (!params)
			return (false);
		params->elements = &minirt->elements;
		params->img = &minirt->mlx;
		params->queue = &minirt->queue;
		params->display = display;
		if (pthread_create(&minirt->threads[minirt->thread_amount], NULL, &start_routine, params))
			return (false);
		minirt->thread_amount++;
	}
	return (true);
}

bool	render_thread(t_rt *minirt)
{
	pthread_cond_wait(&minirt->queue.cond, &minirt->queue.lock);
	if (minirt->queue.ready < minirt->queue.size)
		return (false);
	mlx_put_image_to_window(minirt->mlx.mlx, minirt->mlx.mlx_win, minirt->mlx.img, 0, 0);
	minirt->queue.ready = 0;
	minirt->queue.counter = 0;
	return (true);
}
