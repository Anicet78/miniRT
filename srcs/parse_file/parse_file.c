/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/09/25 16:41:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

bool	finish_parsing(t_elem_lst *elems)
{
	size_t	count;

	count = 0;
	while (count <= elems->frame_amount)
	{
		if (elems->cam[count].declared == false)
			return (frame_err("Camera missing", count + 1));
		if (elems->al[count].declared == false)
			return (frame_err("Ambient Lighting missing", count + 1));
		count++;
	}
	elems->frames[elems->frame_amount++] = elems->count;
	elems->size = elems->count;
	return (true);
}

bool	parse_others(t_elem_lst *elems, char **line, int nb)
{
	if (line[0][0] == '=')
		return (parse_new_frame(elems, line, nb));
	else if (line[0][0] == '^')
		return (parse_goto(elems, line, nb));
	else if (ft_strcmp(line[0], "FPS") == 0)
		return (parse_fps(elems, line, nb));
	else if (ft_strcmp(line[0], "AA") == 0)
		return (add_anti_aliasing(elems, line, nb));
	else if (ft_strcmp(line[0], "BG") == 0)
		return (add_background(elems, line, nb));
	return (print_err("Unknown identifier", nb));
}

bool	parse_elements(t_elem_lst *elems, char **line, int nb)
{
	if (elems->loop)
		return (print_err("You cannot put a new object after a goto", nb));
	if (ft_strcmp(line[0], "A") == 0)
		return (parse_ambient(elems, line, nb));
	else if (ft_strcmp(line[0], "C") == 0)
		return (parse_camera(elems, line, nb));
	else if (ft_strcmp(line[0], "L") == 0)
		return (parse_light(elems, line, nb));
	else if (ft_strcmp(line[0], "pl") == 0)
		return (parse_plane(elems, line, nb));
	else if (ft_strcmp(line[0], "sp") == 0)
		return (parse_sphere(elems, line, nb));
	else if (ft_strcmp(line[0], "cy") == 0)
		return (parse_cylinder(elems, line, nb));
	else if (ft_strcmp(line[0], "co") == 0)
		return (parse_cone(elems, line, nb));
	return (parse_others(elems, line, nb));
}

bool	read_rtfile(int fd, t_elem_lst *elements, t_arena *arena)
{
	char	*line;
	char	**split;
	int		i;

	if (!init_parsing(elements, arena, fd))
		return (false);
	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		split = ft_arena_split(line, ' ', arena);
		free(line);
		if (!split)
			return (print_err("Memory allocation failed", 0));
		if (split[0] && split[0][0] && split[0][0] != '#' && split[0][0] != 10)
		{
			if (parse_elements(elements, split, i) == false)
				return (false);
		}
		i++;
		line = get_next_line(fd);
	}
	if (!finish_parsing(elements))
		return (false);
	return (true);
}
