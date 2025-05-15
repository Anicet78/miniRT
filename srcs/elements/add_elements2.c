/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/15 14:40:00 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder	*add_cylinder(t_elem_lst *elements, t_cylinder *cylinder)
{
	if (!add_element(elements, cylinder, sizeof(t_cylinder)))
		return (NULL);
	return ((t_cylinder *)1);
}

bool	add_new_frame(t_elem_lst *elements, int nb)
{
	elements->frames = ft_realloc(elements->frames, (elements->frame_amount + 2) * sizeof(size_t),
		(elements->frame_amount + 1) * sizeof(size_t));
	if (!elements->frames)
		return (free(elements->frames), print_err("Memory allocation failed in `new frame`", nb));
	elements->frames[elements->frame_amount] = elements->count;
	elements->frame_amount++;
	return (true);
}
