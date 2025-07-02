/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:21 by agruet            #+#    #+#             */
/*   Updated: 2025/06/17 16:27:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "miniRT.h"
# include <pthread.h>
# include <sys/time.h>

# define RENDER_THREADS 3
# define BLOCK_SIZE 32

typedef struct s_mlx		t_mlx;
typedef struct s_miniRT		t_rt;
typedef struct s_display	t_display;

typedef struct s_block
{
	size_t		img_index;
	uint32_t	x_start;
	uint32_t	y_start;
	uint32_t	width;
	uint32_t	height;
}	t_block;

typedef struct s_queue
{
	t_block			*blocks;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	size_t			render_index;
	size_t			print_index;
	uint32_t		counter;
	uint32_t		size;
	uint32_t		*ready;
	bool			stop;
}	t_queue;

typedef struct s_params
{
	t_elem_lst	elements;
	t_mlx		*mlx;
	t_queue		*queue;
	t_display	*display;
	t_arena		*arena;
}	t_params;

// threads
void	init_threads(t_rt *rt, t_display *display);
void	render_thread(t_rt *rt);
void	*start_routine(void *param);
void	wait_image(t_rt *rt);

// queue
void	init_queue(t_rt *rt);
bool	get_next_block(t_block *block, t_queue *queue, t_elem_lst *elems);
void	set_ready(t_queue *queue, t_block *block, t_mlx *mlx);
void	reset_ready(t_queue *queue, t_elem_lst *elems, size_t start);

#endif
