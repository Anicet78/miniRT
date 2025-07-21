/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:09:34 by agruet            #+#    #+#             */
/*   Updated: 2025/07/21 13:41:03 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_ready(t_queue *queue, t_block *block)
{
	pthread_mutex_lock(&queue->lock);
	queue->ready[block->img_index]++;
	if (queue->ready[block->img_index] >= queue->size)
		queue->print_index = block->img_index + 1;
	pthread_mutex_unlock(&queue->lock);
}

void	reset_ready(t_queue *queue, t_elem_lst *elems, size_t start)
{
	while (start < elems->frame_amount)
		queue->ready[start++] = 0;
}

bool	get_next_block(t_block *block, t_queue *queue, t_elem_lst *elems)
{
	pthread_mutex_lock(&queue->lock);
	if (queue->stop == true)
		return (pthread_mutex_unlock(&queue->lock), false);
	if (queue->counter >= queue->size)
	{
		queue->render_index++;
		if (queue->render_index >= elems->frame_amount)
			return (pthread_mutex_unlock(&queue->lock), false);
		queue->counter = 0;
	}
	*block = queue->blocks[queue->counter];
	block->img_index = queue->render_index;
	queue->counter++;
	pthread_mutex_unlock(&queue->lock);
	return (true);
}

static void	fill_block(t_block *block, uint32_t px_start[2], int32_t width,
			int32_t height)
{
	if (px_start[0] + BLOCK_SIZE > (uint32_t)width)
	{
		px_start[0] = 0;
		px_start[1] += BLOCK_SIZE;
	}
	block->x_start = px_start[0];
	block->y_start = px_start[1];
	block->width = ft_min(BLOCK_SIZE, width - px_start[0]);
	block->height = ft_min(BLOCK_SIZE, height - px_start[1]);
}

void	init_queue(t_rt *rt)
{
	const size_t	count_x = (rt->mlx.width + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	count_y = (rt->mlx.height + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	size = count_x * count_y;
	uint32_t		px_start[2];

	rt->queue.blocks = arena_alloc(sizeof(t_block) * size, rt->arena);
	rt->queue.ready = arena_calloc(rt->arena, sizeof(uint32_t)
			* rt->mlx.img_amount);
	if (!rt->queue.blocks || !rt->queue.ready)
		kill_mlx(rt, 1);
	rt->queue.counter = 0;
	rt->queue.render_index = rt->mlx.img_amount;
	rt->queue.print_index = 0;
	rt->queue.size = size;
	rt->queue.stop = false;
	px_start[0] = 0;
	px_start[1] = 0;
	while (rt->queue.counter < size)
	{
		fill_block(&rt->queue.blocks[rt->queue.counter],
			px_start, rt->mlx.width, rt->mlx.height);
		rt->queue.counter++;
		px_start[0] += BLOCK_SIZE;
	}
}
