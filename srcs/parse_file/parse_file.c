/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:21:35 by agruet            #+#    #+#             */
/*   Updated: 2025/06/16 15:48:13 by agruet           ###   ########.fr       */
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
	if (!gnl)
		return (0);
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

bool	alloc_lights(t_light **lights, t_arena *arena, int fd, size_t frames)
{
	size_t	frame;
	size_t	count_lights;
	char	*gnl;

	frame = 0;
	count_lights = 0;
	gnl = get_next_line(fd);
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
			lights[frame] = arena_calloc(arena, sizeof(t_light) * (count_lights + 1));
			if (!lights[frame])
				return (free(gnl), print_err("Memory allocation failed", 0));
			count_lights = 0;
			frame++;
		}
		free(gnl);
		gnl = get_next_line(fd);
	}
	if (count_lights == 0)
		return (frame_err("Light missing", frame + 1));
	lights[frame] = arena_calloc(arena, sizeof(t_light) * (count_lights + 1));
	if (!lights[frame])
		return (print_err("Memory allocation failed", 0));
	lseek(fd, 0, SEEK_SET);
	return (true);
}

bool	alloc_planes(t_plane **planes, t_arena *arena, int fd, size_t frames)
{
	size_t	frame;
	size_t	count_planes;
	char	*gnl;

	frame = 0;
	count_planes = 0;
	gnl = get_next_line(fd);
	if (!gnl)
		return (print_err("An error has occured while reading the file", 0));
	while (gnl && frame < frames)
	{
		if (gnl[0] == 'p' && gnl[1] == 'l' && gnl[2] == ' ')
			count_planes++;
		if (gnl[0] == '=')
		{
			if (count_planes > 0)
				planes[frame] = arena_calloc(arena, sizeof(t_plane) * (count_planes + 1));
			if (count_planes > 0 && !planes[frame])
				return (free(gnl), print_err("Memory allocation failed", 0));
			count_planes = 0;
			frame++;
		}
		free(gnl);
		gnl = get_next_line(fd);
	}
	if (count_planes > 0)
		planes[frame] = arena_calloc(arena, sizeof(t_plane) * (count_planes + 1));
	if (count_planes > 0 && !planes[frame])
		return (print_err("Memory allocation failed", 0));
	lseek(fd, 0, SEEK_SET);
	return (true);
}

size_t	count_elems(char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	dir = opendir(dirname);
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG && entry->d_name[0] != '.')
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

bool	init_parsing(t_elem_lst *elems, t_arena *arena, int fd)
{
	elems->texture_amount = count_elems("textures");
	elems->textures = arena_calloc(arena, sizeof(t_image) * elems->texture_amount);
	if (!elems->textures)
		return (print_err("Memory allocation failed", 0));
	elems->normal_amount = count_elems("normals");
	elems->normals = arena_calloc(arena, sizeof(t_image) * elems->normal_amount);
	if (!elems->normals)
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
	elems->lights = arena_calloc(arena, sizeof(t_light *) * elems->frame_amount);
	if (!elems->lights)
		return (print_err("Memory allocation failed", 0));
	if (!alloc_lights(elems->lights, arena, fd, elems->frame_amount))
		return (false);
	elems->planes = arena_calloc(arena, sizeof(t_plane *) * elems->frame_amount);
	if (!elems->planes)
		return (print_err("Memory allocation failed", 0));
	if (!alloc_planes(elems->planes, arena, fd, elems->frame_amount))
		return (false);
	elems->light_index = 0;
	elems->plane_index = 0;
	elems->frame_amount = 0;
	elems->loop = 0;
	elems->loop_index = 0;
	return (true);
}

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
	else if (line[0][0] == '=')
		return (parse_new_frame(elems, line, nb));
	else if (line[0][0] == '^')
		return (parse_goto(elems, line, nb));
	else if (ft_strcmp(line[0], "FPS") == 0)
		return (parse_fps(elems, line, nb));
	return (print_err("Unknown identifier", nb));
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
		if (split[0] && split[0][0] && split[0][0] != '\n')
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
