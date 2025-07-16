/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:00:55 by agruet            #+#    #+#             */
/*   Updated: 2025/07/16 16:34:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	finish_lights(t_light **lights, t_arena *arena,
	size_t count_lights, size_t frame)
{
	if (count_lights == 0)
		return (frame_err("Light missing", frame + 1));
	lights[frame] = arena_calloc(arena, sizeof(t_light) * (count_lights + 1));
	if (!lights[frame])
		return (print_err("Memory allocation failed", 0));
	return (true);
}

bool	alloc_lights(t_light **lights, t_arena *arena, int fd, size_t frames)
{
	auto size_t frame = 0;
	auto size_t count_lights = 0;
	auto char *gnl = get_next_line(fd);
	if (!gnl)
		return (print_err("An error has occured while reading the file", 0));
	while (gnl && frame < frames)
	{
		if (gnl[0] == 'L')
			count_lights++;
		if (gnl[0] == '=')
		{
			if (count_lights == 0)
				return (free(gnl), frame_err("Light missing", frame + 1));
			lights[frame] = arena_calloc(arena, sizeof(t_light)
					* (count_lights + 1));
			if (!lights[frame])
				return (free(gnl), print_err("Memory allocation failed", 0));
			count_lights = 0;
			frame++;
		}
		free(gnl);
		gnl = get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (finish_lights(lights, arena, count_lights, frame));
}

static bool	finish_planes(t_plane **planes, t_arena *arena,
	size_t count_planes, size_t frame)
{
	if (count_planes > 0)
		planes[frame] = arena_calloc(arena, sizeof(t_plane)
				* (count_planes + 1));
	if (count_planes > 0 && !planes[frame])
		return (print_err("Memory allocation failed", 0));
	return (true);
}

bool	alloc_planes(t_plane **planes, t_arena *arena, int fd, size_t frames)
{
	auto size_t frame = 0;
	auto size_t count_planes = 0;
	auto char *gnl = get_next_line(fd);
	if (!gnl)
		return (print_err("An error has occured while reading the file", 0));
	while (gnl && frame < frames)
	{
		if (gnl[0] == 'p' && gnl[1] == 'l' && gnl[2] == ' ')
			count_planes++;
		if (gnl[0] == '=')
		{
			if (count_planes > 0)
				planes[frame] = arena_calloc(arena, sizeof(t_plane)
						* (count_planes + 1));
			if (count_planes > 0 && !planes[frame])
				return (free(gnl), print_err("Memory allocation failed", 0));
			count_planes = 0;
			frame++;
		}
		free(gnl);
		gnl = get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (finish_planes(planes, arena, count_planes, frame));
}
