/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:16:00 by agruet            #+#    #+#             */
/*   Updated: 2025/09/09 19:11:06 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

uint8_t	get_elem_type(void *elem)
{
	return (*(uint8_t *)elem);
}

size_t	get_elem_size(void *elem)
{
	uint8_t	type;

	type = get_elem_type(elem);
	if (type == SPHERE)
		return (sizeof(t_sphere));
	if (type == CYLINDER)
		return (sizeof(t_cylinder));
	if (type == PLANE)
		return (sizeof(t_plane));
	if (type == AMBIENT_LIGHTING)
		return (sizeof(t_ambient));
	if (type == LIGHT)
		return (sizeof(t_light));
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
