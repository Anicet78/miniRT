/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/05/06 14:09:16 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	**ft_arena_split(char const *s, char c, t_arena *arena)
{
	char	**tab;
	int		words;
	int		i;
	int		j;
	int		k;

	words = count_words(s, c);
	tab = arena_calloc(arena, (words + 1) * sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] && i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		k = j;
		while (s[j] && s[j] != c)
			j++;
		tab[i] = arena_calloc(arena, (j - k + 1) * sizeof(char));
		if (!tab[i])
			return (NULL);
		ft_strlcpy(tab[i++], s + k, j - k + 1);
	}
	return (tab);
}

bool	parse_elements(t_elem_lst *elements, char **line, int nb)
{
	if (ft_strcmp(line[0], "A") == 0)
		return (parse_ambient(elements, line, nb));
	else if (ft_strcmp(line[0], "C") == 0)
		return (parse_camera(elements, line, nb));
	else if (ft_strcmp(line[0], "L") == 0)
		return (parse_light(elements, line, nb));
	else if (ft_strcmp(line[0], "pl") == 0)
		return (parse_plane(elements, line, nb));
	else if (ft_strcmp(line[0], "sp") == 0)
		return (parse_sphere(elements, line, nb));
	else if (ft_strcmp(line[0], "cy") == 0)
		return (parse_cylinder(elements, line, nb));
	return (print_err("Unknown identifier", nb));
}

bool	read_rtfile(int fd, t_elem_lst *elements)
{
	char	*line;
	char	**split;
	int		i;

	i = 1;
	elements->cam.declared = false;
	line = get_next_line(fd);
	while (line)
	{
		split = ft_arena_split(line, ' ', elements->arena);
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
	if (elements->cam.declared == false)
		return (print_err("Camera missing", 0));
	return (true);
}
