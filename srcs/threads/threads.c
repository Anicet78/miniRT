/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:52:58 by agruet            #+#    #+#             */
/*   Updated: 2025/05/21 16:26:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	init_mutex(t_queue *queue, pthread_attr_t *attr)
{
	if (pthread_mutex_init(&queue->lock, NULL))
		return (false);
	if (pthread_cond_init(&queue->cond, NULL))
	{
		pthread_mutex_destroy(&queue->lock);
		return (false);
	}
	if(pthread_attr_init(attr))
	{
		pthread_mutex_destroy(&queue->lock);
		pthread_cond_destroy(&queue->cond);
		return (false);
	}
	if (pthread_attr_setstacksize(attr, 1048576))
	{
		pthread_mutex_destroy(&queue->lock);
		pthread_cond_destroy(&queue->cond);
		pthread_attr_destroy(attr);
		return (false);
	}
	return (true);
}

static bool	init_params(t_rt *rt, t_display *display, t_params *params)
{
	t_camera	*cams;

	params->elements = rt->elements;
	params->elements.elem_lst = arena_calloc(params->arena, rt->elements.size * 10);
	if (!params->elements.elem_lst)
		return (false);
	ft_memmove(params->elements.elem_lst, rt->elements.elem_lst, rt->elements.size * 10);
	cams = params->elements.cam;
	params->elements.cam = arena_alloc(sizeof(t_camera) * rt->elements.frame_amount,
		params->arena);
	if (!params->elements.cam)
		return (false);
	ft_memmove(params->elements.cam, cams, sizeof(t_camera) * rt->elements.frame_amount);
	params->mlx = &rt->mlx;
	params->queue = &rt->queue;
	params->display = display;
	return (true);
}

static size_t	get_arena_size(t_rt *rt)
{
	return ((rt->elements.size + sizeof(t_camera) * rt->elements.frame_amount) * 10);
}

static bool	new_thread(t_rt *rt, t_display *display, pthread_attr_t *attr)
{
	t_arena		*memdup;
	t_params	*params;

	params = arena_alloc(sizeof(t_params), rt->arena);
	if (!params)
		return (false);
	memdup = arena_init(get_arena_size(rt) + 1);
	if (!memdup)
		return (false);
	params->arena = memdup;
	if (!init_params(rt, display, params))
		return (false);
	if (pthread_create(&rt->threads[rt->thread_amount], attr, &start_routine, params))
		return (false);
	return (true);
}

void	init_threads(t_rt *rt, t_display *display)
{
	t_params		*params;
	pthread_attr_t	attr;

	if (init_mutex(&rt->queue, &attr) == false)
		kill_mlx(rt, 1);
	rt->threads = arena_alloc(sizeof(pthread_t) * RENDER_THREADS, rt->arena);
	if (!rt->threads)
		(pthread_attr_destroy(&attr), kill_mlx(rt, 1));
	pthread_mutex_lock(&rt->queue.lock);
	while (rt->thread_amount < RENDER_THREADS)
	{
		if (!new_thread(rt, display, &attr))
			(pthread_attr_destroy(&attr), kill_mlx(rt, 1));
		rt->thread_amount++;
	}
	pthread_attr_destroy(&attr);
}
