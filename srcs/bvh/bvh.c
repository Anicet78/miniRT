/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:43 by agruet            #+#    #+#             */
/*   Updated: 2025/06/06 17:39:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	create_bvh(t_rt *rt, t_elem_lst *elems)
{
	elems->bvh = arena_calloc(rt->arena, * elems->elem_amount);
	if (!elems->bvh)
	{
		print_err("Memory allocation failed", 0);
		kill_mlx(rt, 1);
	}
}
