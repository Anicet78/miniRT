/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:09:34 by agruet            #+#    #+#             */
/*   Updated: 2025/05/19 12:00:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_ready(t_queue *queue, t_block *block)
{
	pthread_mutex_lock(&queue->lock);
	queue->ready[block->img_index]++;
	if (queue->ready[block->img_index] >= queue->size)
	{
		queue->print_index = block->img_index;
		pthread_cond_signal(&queue->cond);
	}
	pthread_mutex_unlock(&queue->lock);
}

bool	get_next_block(t_block *block, t_queue *queue, t_mlx *mlx)
{
	pthread_mutex_lock(&queue->lock);
	if (queue->counter >= queue->size)
	{
		if (queue->render_index + 1 >= mlx->img_amount)
			return (pthread_mutex_unlock(&queue->lock), false);
		queue->render_index++;
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
	block->x_start = px_start[0];
	block->y_start = px_start[1];
	block->width = ft_min(BLOCK_SIZE, width - px_start[0]);
	block->height = ft_min(BLOCK_SIZE, height - px_start[1]);
}

bool	init_queue(t_rt *rt)
{
	const size_t	count_x = (rt->mlx.width + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	count_y = (rt->mlx.height + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	size = count_x * count_y;
	uint32_t		px_start[2];

	rt->queue.blocks = arena_alloc(sizeof(t_block) * size, rt->arena);
	rt->queue.ready = arena_calloc(rt->arena, sizeof(uint32_t) * rt->mlx.img_amount);
	if (!rt->queue.blocks || !rt->queue.ready)
		return (false);
	rt->queue.counter = 0;
	rt->queue.render_index = rt->mlx.img_amount;
	rt->queue.print_index = 0;
	rt->queue.size = size;
	px_start[0] = 0;
	px_start[1] = 0;
	while (rt->queue.counter < size)
	{
		if (px_start[0] + BLOCK_SIZE > rt->mlx.width)
		{
			px_start[0] = 0;
			px_start[1] += BLOCK_SIZE;
		}
		fill_block(&rt->queue.blocks[rt->queue.counter],
			px_start, rt->mlx.width, rt->mlx.height);
		rt->queue.counter++;
		px_start[0] += BLOCK_SIZE;
	}
	return (true);
}
