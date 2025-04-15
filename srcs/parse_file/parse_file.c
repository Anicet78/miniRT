/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 17:04:40 by agruet           ###   ########.fr       */
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

bool	parse_elements(t_elem_lst *elements, char **line)
{
	static int	ambient = 0;
	static int	camera = 0;
	static int	light = 0;

	if (ft_strcmp(line[0], "A") == 0 && ambient++ == 0)
		return (parse_ambient(elements, line));
	else if (ft_strcmp(line[0], "C") == 0 && camera++ == 0)
		return (parse_camera(elements, line));
	else if (ft_strcmp(line[0], "L") == 0 && light++ == 0)
		return (parse_light(elements, line));
	else if (ft_strcmp(line[0], "pl") == 0)
		return (parse_plane(elements, line));
	else if (ft_strcmp(line[0], "sp") == 0)
		return (parse_sphere(elements, line));
	else if (ft_strcmp(line[0], "cy") == 0)
		return (parse_cylinder(elements, line));
	return (false);
}

bool	read_rtfile(int fd, t_elem_lst *elements)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	if (!line)
		return (false);
	while (line)
	{
		split = ft_arena_split(line, ' ', elements->arena);
		free(line);
		if (!split)
			return (false);
		if (split[0])
		{
			if (parse_elements(elements, split) == false)
				return (false);
		}
		line = get_next_line(fd);
	}
	return (true);
}
