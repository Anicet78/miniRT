/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_displays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:35:15 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:14:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

t_display	*init_all_displays(t_camera *cam, t_arena *arena,
	size_t frame_amount)
{
	size_t		count;
	t_display	*displays;

	displays = arena_alloc(sizeof(t_display) * frame_amount, arena);
	if (!displays)
		return (NULL);
	count = 0;
	while (count < frame_amount)
	{
		displays[count] = init_display(&cam[count]);
		count++;
	}
	return (displays);
}
