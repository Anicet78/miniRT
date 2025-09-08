/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:26:41 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:14:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

static bool	alloc_first(t_elem_lst *elems, t_arena *arena, int fd)
{
	elems->texture_amount = count_elems("textures");
	elems->textures = arena_calloc(arena, sizeof(t_image)
			* elems->texture_amount);
	if (!elems->textures)
		return (print_err("Memory allocation failed", 0));
	elems->bmaps_amount = count_elems("bump_maps");
	elems->bmaps = arena_calloc(arena, sizeof(t_image)
			* elems->bmaps_amount);
	if (!elems->bmaps)
		return (print_err("Memory allocation failed", 0));
	elems->frame_amount = count_frames(fd);
	if (elems->frame_amount == 0)
		return (print_err("An error has occured while reading the file", 0));
	elems->frames = arena_calloc(arena, sizeof(size_t) * elems->frame_amount);
	if (!elems->frames)
		return (print_err("Memory allocation failed", 0));
	elems->cam = arena_calloc(arena, sizeof(t_camera) * elems->frame_amount);
	if (!elems->cam)
		return (print_err("Memory allocation failed", 0));
	elems->al = arena_calloc(arena, sizeof(t_ambient) * elems->frame_amount);
	if (!elems->al)
		return (print_err("Memory allocation failed", 0));
	return (true);
}

bool	init_parsing(t_elem_lst *elems, t_arena *arena, int fd)
{
	if (!alloc_first(elems, arena, fd))
		return (false);
	elems->lights = arena_calloc(arena, sizeof(t_light *)
			* elems->frame_amount);
	if (!elems->lights)
		return (print_err("Memory allocation failed", 0));
	if (!alloc_lights(elems->lights, arena, fd, elems->frame_amount))
		return (false);
	elems->planes = arena_calloc(arena, sizeof(t_plane *)
			* elems->frame_amount);
	if (!elems->planes)
		return (print_err("Memory allocation failed", 0));
	if (!alloc_planes(elems->planes, arena, fd, elems->frame_amount))
		return (false);
	elems->light_index = 0;
	elems->plane_index = 0;
	elems->frame_amount = 0;
	elems->loop = 0;
	elems->loop_index = 0;
	elems->fps = 60;
	return (true);
}
