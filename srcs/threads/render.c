/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:21:01 by agruet            #+#    #+#             */
/*   Updated: 2025/05/20 12:16:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	print_pixels(t_block block, t_params *p, t_mlx *mlx, t_queue *queue)
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
				ray_to_color(&r, (t_elem_lst *)&elems, elems.frames[block.img_index]));
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
		if (!get_next_block(&block, params->queue, params->mlx))
			return (clear_arena(&params->arena), NULL);
		print_pixels(block, params, params->mlx, params->queue);
		set_ready(params->queue, &block);
	}
	return (NULL);
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
		mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.mlx_win,
			rt->mlx.imgs[rt->queue.print_index++], 0, 0);
	}
	return (true);
}