/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:16:00 by agruet            #+#    #+#             */
/*   Updated: 2025/05/06 13:43:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_elem_lst	*new_elem_list(t_elem_lst *elements)
{
	elements->capacity = CHUNK_SIZE * 90 / 100;
	elements->arena = arena_init();
	if (!elements->arena)
		return (NULL);
	elements->count = 0;
	elements->elem_lst = arena_calloc(elements->arena, elements->capacity);
	if (!elements->elem_lst)
		return (NULL);
	return (elements);
}

t_elem_type	get_elem_type(void *elem)
{
	return (*(t_elem_type *)elem);
}

size_t	get_elem_size(void *elem)
{
	t_elem_type	type;

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

	if (elements->count >= elements->capacity)
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
	if (elements->count + size > elements->capacity)
	{
		print_err("Memory allocation failed: chunk size too small", 0);
		return (clear_arena(&elements->arena), NULL);
	}
	ft_memcpy(elements->elem_lst + elements->count, new_elem, size);
	elements->count += size;
	return (elements);
}
