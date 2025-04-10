/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:14:51 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 15:28:01 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_searching_dir(char *buff, t_rline *line)
{
	size_t	i;
	size_t	start;
	char	*chr;

	ft_memset(buff, 0, 512);
	i = line->tab_index;
	while (i > 0 && line->current_line[i] != ' ')
		i--;
	if (line->current_line[i] == ' ')
		i++;
	chr = ft_strchr(line->current_line + i, '/');
	if (!chr || chr > line->current_line + line->tab_index)
	{
		buff[0] = '.';
		return (buff);
	}
	start = i;
	while (chr && chr < line->current_line + line->tab_index)
	{
		ft_strlcat(buff, line->current_line + i,
			(chr - (line->current_line + start)) + 1);
		i = chr - line->current_line;
		chr = ft_strchr(line->current_line + i + 1, '/');
	}
	return (buff);
}

static int	check_entry(struct dirent *entry, t_rline *line)
{
	size_t	i;

	if (entry->d_type != DT_REG && entry->d_type != DT_DIR
		&& entry->d_type != DT_LNK)
		return (0);
	if (entry->d_name[0] == '.')
		return (0);
	i = line->tab_index;
	while (i > 0 && line->current_line[i] != ' '
		&& line->current_line[i] != '/')
		i--;
	if (line->current_line[i] == ' ' || line->current_line[i] == '/')
		i++;
	if (ft_strncmp(entry->d_name, line->current_line + i, line->tab_index - i))
		return (0);
	return (1);
}

static struct dirent	*get_next_entry(t_rline *line)
{
	struct dirent	*entry;
	char			dir_buff[512];

	if (ft_strcmp(line->searching_dir, get_searching_dir(dir_buff, line)))
	{
		closedir(line->dir);
		ft_strlcpy(line->searching_dir, dir_buff, ft_strlen(dir_buff) + 1);
		line->dir = opendir(line->searching_dir);
		if (!line->dir)
			return (ft_strlcpy(line->searching_dir, ".", 3), NULL);
	}
	entry = readdir(line->dir);
	while (entry && !check_entry(entry, line))
		entry = readdir(line->dir);
	if (!entry)
	{
		closedir(line->dir);
		line->dir = opendir(line->searching_dir);
		entry = readdir(line->dir);
		if (!line->dir)
			return (ft_strlcpy(line->searching_dir, ".", 3), NULL);
	}
	while (entry && !check_entry(entry, line))
		entry = readdir(line->dir);
	return (entry);
}

static void	apply_entry(struct dirent *entry, t_rline *line, t_readline *params)
{
	size_t	i;
	size_t	j;

	while (line->cursor > 0 && line->cursor > line->tab_index)
		back_space(line);
	i = line->tab_index;
	while (i > 0 && line->current_line[i] != ' '
		&& line->current_line[i] != '/')
		i--;
	if (line->current_line[i] == ' ' || line->current_line[i] == '/')
		i++;
	j = 0;
	while (entry->d_name[j] && line->current_line[i + j] == entry->d_name[j])
		j++;
	line->end += j;
	if (!line_too_long(line, params->history))
		return ;
	line->end -= j;
	while (entry->d_name[j])
		printkey(entry->d_name[j++], line, params);
	line->auto_type = entry->d_type;
}

int	auto_complete(int key, t_rline *line, t_readline *params)
{
	struct dirent	*entry;

	if (!isatty(STDIN_FILENO) || !line->current_line)
		return (0);
	if (key != '\t' && key != '\n' && key != READ_FAILED)
	{
		line->in_auto = false;
		line->auto_type = DT_UNKNOWN;
		return (0);
	}
	if ((key == '\n' || key == READ_FAILED) && line->in_auto == false)
		return (0);
	if (line->in_auto == false)
	{
		line->tab_index = line->cursor;
		line->in_auto = true;
	}
	if (key == '\n' || key == READ_FAILED)
		return (expand_current(key, line, params));
	entry = get_next_entry(line);
	if (!entry)
		return (1);
	apply_entry(entry, line, params);
	return (1);
}
