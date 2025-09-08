/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:53:30 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 14:04:58 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	calc_arena_size(int fd)
{
	size_t	size;
	char	*gnl;

	size = 1;
	gnl = get_next_line(fd);
	while (gnl)
	{
		size++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (size * sizeof(t_cylinder) * 10);
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
