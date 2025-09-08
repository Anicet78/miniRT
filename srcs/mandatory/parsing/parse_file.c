/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:11:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

static bool	finish_mand_parsing(t_elem_lst *elems)
{
	if (elems->cam.declared == false)
		return (print_err("Camera missing", 0));
	if (elems->amb.declared == false)
		return (print_err("Ambient Lighting missing", 0));
	if (elems->light.declared == false)
		return (print_err("Lighting missing", 0));
	return (true);
}

static bool	parse_elements(t_elem_lst *elems, char **line, int nb)
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

bool	mand_parsing(int fd, t_elem_lst *elements, t_arena *arena)
{
	char	*line;
	char	**split;
	int		i;

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
	return (finish_mand_parsing(elements));
}
