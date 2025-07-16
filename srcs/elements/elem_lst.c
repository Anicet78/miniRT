/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:16:00 by agruet            #+#    #+#             */
/*   Updated: 2025/07/16 17:02:17 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_elem_lst	*init_minirt(t_rt *rt, int fd)
{
	rt->thread_amount = 0;
	rt->mlx.mlx_win = NULL;
	rt->mlx.imgs = NULL;
	rt->mlx.addr = NULL;
	rt->elements.textures = NULL;
	rt->elements.normals = NULL;
	rt->elements.allocated_size = calc_arena_size(fd);
	rt->arena = arena_init(rt->elements.allocated_size);
	if (!rt->arena)
		return (print_err("Memory allocation failed", 0), NULL);
	rt->elements.count = 0;
	rt->elements.allocated_size = rt->elements.allocated_size * 90 / 100;
	rt->elements.elem_lst = arena_calloc(rt->arena,
			rt->elements.allocated_size);
	if (!rt->elements.elem_lst)
	{
		clear_arena(&rt->arena);
		print_err("Memory allocation failed", 0);
		return (NULL);
	}
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		kill_mlx(rt, EXIT_FAILURE);
	rt->elements.mlx_ptr = rt->mlx.mlx;
	return (&rt->elements);
}

uint8_t	get_elem_type(void *elem)
{
	return (*(uint8_t *)elem);
}

size_t	get_elem_size(void *elem)
{
	uint8_t	type;

	type = get_elem_type(elem);
	if (type == AMBIENT_LIGHTING)
		return (sizeof(t_ambient));
	if (type == LIGHT)
		return (sizeof(t_light));
	if (type == SPHERE)
		return (sizeof(t_sphere));
	if (type == PLANE)
		return (sizeof(t_plane));
	if (type == CYLINDER)
		return (sizeof(t_cylinder));
	return (0);
}

void	*get_next_elem(t_elem_lst *elements)
{
	void	*elem;
	size_t	elem_size;

	if (elements->count >= elements->size)
		return (NULL);
	elem = elements->elem_lst + elements->count;
	elem_size = get_elem_size(elem);
	if (elem_size == 0)
		return (NULL);
	elements->count += elem_size;
	return (elem);
}

t_elem_lst	*add_element(t_elem_lst *elements, void *new_elem, size_t size)
{
	if (elements->count + size > elements->allocated_size / 8)
	{
		print_err("Memory allocation failed: chunk size too small", 0);
		return (NULL);
	}
	ft_memmove(elements->elem_lst + elements->count, new_elem, size);
	elements->count += size;
	return (elements);
}
