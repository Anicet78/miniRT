/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/05/19 14:45:52 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	**ft_arena_split(char const *s, char c, t_arena *arena)
{
	char			**tab;
	const int		words = count_words(s, c);
	int				i;
	int				j;
	int				k;

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

size_t	count_frames(int fd)
{
	size_t	frames;
	char	*gnl;

	frames = 1;
	gnl = get_next_line(fd);
	while (gnl)
	{
		if (gnl[0] == '=')
			frames++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (frames);
}

bool	init_parsing(t_elem_lst *elems, t_arena *arena)
{
	elems->frames = arena_calloc(arena, sizeof(size_t) * elems->frame_amount);
	if (!elems->frames)
		return (print_err("Memory allocation failed", 0));
	elems->cam = arena_calloc(arena, sizeof(t_camera) * elems->frame_amount);
	if (!elems->cam)
		return (print_err("Memory allocation failed", 0));
	elems->frame_amount = 0;
	return (true);
}

bool	finish_parsing(t_elem_lst *elems, t_arena *arena)
{
	size_t	count;

	count = 0;
	while (count <= elems->frame_amount)
	{
		if (elems->cam[count].declared == false)
		{
			ft_fprintf(2, "\e[1;31mError\nFrame %d: %s\e[0m\n",
				count + 1, "Camera missing");
			return (false);
		}
		count++;
	}
	elems->frames[elems->frame_amount++] = elems->count;
	elems->size = elems->count;
	return (true);
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
	else if (line[0][0] == '=')
		return (parse_new_frame(elements, line, nb));
	/* else if (ft_strcmp(line[0], "FPS"))
		return (parse_fps(elements, line, nb)); */
	return (print_err("Unknown identifier", nb));
}

bool	read_rtfile(int fd, t_elem_lst *elements, t_arena *arena)
{
	char	*line;
	char	**split;
	int		i;

	elements->frame_amount = count_frames(fd);
	if (init_parsing(elements, arena) == false)
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
	if (!finish_parsing(elements, arena))
		return (false);
	return (true);
}
