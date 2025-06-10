/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/10 17:02:58 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

size_t	count_elem_amount(t_elem_lst *elems)
{
	void	*elem;
	size_t	count;

	elems->count = 0;
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[0])
	{
		count++;
		elem = get_next_elem(elems);
	}
	return (count);
}

void	init_aabb(t_elem_lst *elems)
{
	void	*elem;
	int		type;
	size_t	count;

	elems->count = 0;
	count = 0;
	elem = get_next_elem(elems);
	while (elem && elems->count <= elems->frames[0])
	{
		elems->bvh[count].bbox = get_elem_aabb(elem);
		elems->bvh[count].obj = elem;
		elem = get_next_elem(elems);
		count++;
	}
}

void	create_bvh(t_rt *rt, t_elem_lst *elems)
{
	const size_t	elem_amount = count_elem_amount(elems);
	void			*elem;

	elems->bvh = arena_calloc(rt->arena, sizeof(t_bvh_node) * elem_amount);
	if (!elems->bvh)
	{
		print_err("Memory allocation failed", 0);
		kill_mlx(rt, 1);
	}
	init_aabb(elems);
}
