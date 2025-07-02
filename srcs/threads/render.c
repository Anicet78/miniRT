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
			return (clear_arena(&params->arena), NULL);
		print_pixels(block, params, params->mlx);
		set_ready(params->queue, &block, params->mlx);
	}
	return (NULL);
}

void	wait_image(t_rt *rt)
{
	static size_t	last_frame = 0;
	static long		time;
	long			current;

	if (last_frame >= rt->elements.frame_amount && !rt->elements.loop)
		return ;
	if (time == 0)
		time = get_time_now();
	current = get_time_now();
	if (current > time)
	{
		while (true)
		{
			pthread_mutex_lock(&rt->queue.lock);
			pthread_cond_wait(&rt->queue.cond, &rt->queue.lock);
			last_frame = rt->queue.print_index;
			pthread_mutex_unlock(&rt->queue.lock);
			mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
				rt->mlx.imgs[last_frame], 0, 0);
			time = current;
			break ;
		}
	}
}

void	render_thread(t_rt *rt)
{
	rt->queue.counter = 0;
	rt->queue.render_index = 0;
	rt->elements.count = 0;
	pthread_mutex_unlock(&rt->queue.lock);
}
