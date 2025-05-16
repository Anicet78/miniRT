/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:52:58 by agruet            #+#    #+#             */
/*   Updated: 2025/05/16 15:52:14 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	print_pixels(t_block block, t_params *p, t_mlx *mlx, t_queue *queue)
{
	uint32_t			x;
	uint32_t			y;
	t_ray				r;
	t_point				world_pix;
	const t_elem_lst	*elems = p->elements;
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
			r.dir = norm(vsub(world_pix, elems->cam[block.img_index].pos));
			r.p = elems->cam[block.img_index].pos;
			put_pixel_to_img(mlx, mlx->addr[block.img_index], (uint32_t[2]){x, y},
				ray_to_color(&r, (t_elem_lst *)elems, elems->frames[block.img_index]));
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
		block_ptr = get_next_block(params->queue, params->mlx);
		if (!block_ptr)
			return (NULL);
		print_pixels(*block_ptr, params, params->mlx, params->queue);
		set_ready(params->queue, block_ptr);
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

bool	init_threads(t_rt *rt, t_display *display)
{
	t_params	*params;

	if (init_mutex(&rt->queue) == false)
		return (false);
	rt->threads = arena_alloc(sizeof(pthread_t) * RENDER_THREADS, rt->arena);
	if (!rt->threads)
		return (false);
	pthread_mutex_lock(&rt->queue.lock);
	while (rt->thread_amount < RENDER_THREADS)
	{
		params = arena_alloc(sizeof(t_params), rt->arena);
		if (!params)
			return (false);
		params->elements = &rt->elements;
		params->mlx = &rt->mlx;
		params->queue = &rt->queue;
		params->display = display;
		if (pthread_create(&rt->threads[rt->thread_amount], NULL, &start_routine, params))
			return (false);
		rt->thread_amount++;
	}
	return (true);
}

bool	render_thread(t_rt *rt)
{
	rt->queue.counter = 0;
	rt->queue.render_index = 0;
	while (rt->queue.print_index < rt->mlx.img_amount)
	{
		pthread_cond_wait(&rt->queue.cond, &rt->queue.lock);
		// sleep for fps (mlx loop at the same time ?)
		// print fps
		mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win, rt->mlx.imgs[rt->queue.print_index], 0, 0);
		rt->queue.print_index++;
	}
	return (true);
}
