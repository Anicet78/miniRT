/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:21 by agruet            #+#    #+#             */
/*   Updated: 2025/05/10 16:35:41 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "miniRT.h"
# include <pthread.h>
# include <sys/time.h>

# define BLOCK_SIZE 32

typedef struct s_mlx	t_mlx;
typedef struct s_miniRT	t_miniRT;

typedef struct s_block
{
	uint32_t	x_start;
	uint32_t	y_start;
	uint32_t	width;
	uint32_t	height;
}	t_block;

typedef struct s_queue
{
	t_block			*blocks;
	pthread_mutex_t	lock;
	uint32_t		counter;
	uint32_t		size;
}	t_queue;

typedef struct s_params
{
	t_elem_lst	*elements;
	t_mlx		*img;
	uint64_t	pixel_start;
	uint32_t	pixel_amount;
	uint32_t	width;
	uint32_t	height;
}	t_params;

// threads
bool	init_threads(t_miniRT *minirt);

// queue
bool	init_queue(t_miniRT *minirt);

#endif
