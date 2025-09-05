/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/09/05 18:18:59 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	count_plane(int fd);

bool	init_mandparsing(t_mandlst *elems, t_arena *arena, const char *file)
{
	const int	nb_plane = count_plane(fd);

	elems->pl = arena_calloc(arena, sizeof(t_plane)
			* nb_plane);
	if (!elems->pl)
		return (print_err("Memory allocation failed", 0));
	return (true);
}

bool	parse_elements(t_mandlst *elems, char **line, int nb)
{
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
	return (print_err("Unknown identifier", nb));
}

bool	mand_parsing(const char *file, t_mandlst *elements, t_arena *arena)
{
	char	*line;
	char	**split;
	int		i;

	if (!init_mandparsing(file, elements, arena))
		return (false);
	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		split = ft_arena_split(line, ' ', arena);
		free(line);
		if (!split)
			return (print_err("Memory allocation failed", 0));
		if (split[0] && split[0][0] && split[0][0] != '\n')
		{
			if (parse_elements(elements, split, i) == false)
				return (false);
		}
		i++;
		line = get_next_line(fd);
	}
	return (true);
}
