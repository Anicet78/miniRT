/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_elem_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:16:00 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 19:28:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	*mand_get_next_elem(t_mandlst *elements)
{
	void	*elem;
	size_t	elem_size;

	if (elements->lst_count >= elements->lst_size)
		return (NULL);
	elem = elements->elem_lst + elements->lst_count;
	elem_size = get_elem_size(elem);
	if (elem_size == 0)
		return (NULL);
	elements->lst_count += elem_size;
	return (elem);
}

t_mandlst	*mand_add_element(t_mandlst *elements, void *new_elem, size_t size)
{
	if (elements->lst_count + size > elements->allocated_size / 8)
	{
		print_err("Memory allocation failed: chunk size too small", 0);
		return (NULL);
	}
	ft_memmove(elements->elem_lst + elements->lst_count, new_elem, size);
	elements->lst_count += size;
	return (elements);
}
