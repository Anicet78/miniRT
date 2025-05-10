/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:09:34 by agruet            #+#    #+#             */
/*   Updated: 2025/05/10 16:50:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	init_queue(t_miniRT *minirt)
{
	const size_t	count_x = (minirt->mlx.width + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	count_y = (minirt->mlx.height + BLOCK_SIZE - 1) / BLOCK_SIZE;
	const size_t	size = count_x * count_y;

	minirt->queue = arena_alloc(sizeof(t_queue), minirt->arena);
	if (!minirt->queue)
		return (false);
	minirt->queue->blocks = malloc(sizeof(t_block) * size);
	if (!minirt->queue->blocks)
		return (false);
	minirt->queue->counter = 0;
	minirt->queue->size = size;
}
