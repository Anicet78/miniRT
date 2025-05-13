/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:09:34 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 18:31:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_ready(t_queue *queue)
{
	pthread_mutex_lock(&queue->lock);
	queue->ready++;
	if (queue->ready >= queue->size)
		pthread_cond_signal(&queue->cond);
	pthread_mutex_unlock(&queue->lock);
}

t_block	*get_next_block(t_queue *queue)
{
	t_block	*block;

	pthread_mutex_lock(&queue->lock);
	if (queue->counter >= queue->size)
		return (pthread_mutex_unlock(&queue->lock), NULL);
	block = &queue->blocks[queue->counter];
	queue->counter++;
	pthread_mutex_unlock(&queue->lock);
	return (block);
}

static void	fill_block(t_block *block, uint32_t px_start[2], int32_t width,
			int32_t height)
{
	block->x_start = px_start[0];
	block->y_start = px_start[1];
	block->width = ft_min(BLOCK_SIZE, width - px_start[0]);
	block->height = ft_min(BLOCK_SIZE, height - px_start[1]);
}

bool	init_queue(t_rt *minirt)
{
	const size_t	count_x = (minirt->mlx.width + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	count_y = (minirt->mlx.height + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	size = count_x * count_y;
	uint32_t		px_start[2];

	minirt->queue.blocks = arena_alloc(sizeof(t_block) * size, minirt->arena);
	if (!minirt->queue.blocks)
		return (false);
	minirt->queue.counter = 0;
	minirt->queue.ready = 0;
	minirt->queue.size = size;
	px_start[0] = 0;
	px_start[1] = 0;
	while (minirt->queue.counter < size)
	{
		if (px_start[0] + BLOCK_SIZE > minirt->mlx.width)
		{
			px_start[0] = 0;
			px_start[1] += BLOCK_SIZE;
		}
		fill_block(&minirt->queue.blocks[minirt->queue.counter],
			px_start, minirt->mlx.width, minirt->mlx.height);
		minirt->queue.counter++;
		px_start[0] += BLOCK_SIZE;
	}
	minirt->queue.counter = 0;
	return (true);
}
