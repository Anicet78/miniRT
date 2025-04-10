/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:45:38 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 00:32:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printkey(int key, t_rline *line, t_readline *params)
{
	size_t	len;
	char	*temp;

	if (key == '\n')
	{
		params->quit_reason = RL_SUCCESS;
		return (1);
	}
	if ((key == '\f' || key == '\t') && isatty(STDIN_FILENO))
		return (0);
	write(STDIN_FILENO, &key, 1);
	len = ft_strlen(line->current_line + line->cursor);
	if (len > 0)
	{
		ft_memmove(line->current_line + line->cursor + 1,
			line->current_line + line->cursor, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor + 1);
		temp = ft_strdup(line->current_line);
		(write_x_times(temp, '\b', len), free(temp));
	}
	line->current_line[line->cursor++] = key;
	line->end++;
	return (0);
}

void	move_key(t_rline*line, int key)
{
	if (key == RARROW && line->cursor < line->end)
	{
		ft_fprintf(0, "\033[C");
		line->cursor++;
	}
	else if (key == LARROW && line->cursor > 0)
	{
		ft_fprintf(0, "\033[D");
		line->cursor--;
	}
}

void	back_space(t_rline*line)
{
	size_t	len;
	char	*temp;

	if (line->cursor <= 0)
		return ;
	len = ft_strlen(line->current_line + line->cursor) + 1;
	temp = ft_strdup(line->current_line);
	write_x_times(temp, ' ', len);
	write_x_times(temp, '\b', len);
	line->cursor--;
	line->end--;
	write(0, "\b \b", 3);
	if (len > 1)
	{
		ft_memmove(line->current_line + line->cursor,
			line->current_line + line->cursor + 1, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor);
		write_x_times(temp, '\b', len - 1);
	}
	free(temp);
	line->current_line[line->end] = '\0';
}

void	del_key(t_rline*line)
{
	if (line->cursor == line->end)
		return ;
	ft_fprintf(0, "%c", line->current_line[line->cursor++]);
	back_space(line);
}

int	other_key(int key, t_rline *line, t_readline *params)
{
	if (key == EOF_K && line->end == 0)
		return (eof_received(line, params));
	else if (key == READ_FAILED || key == FINISH_READING)
		return (rl_signal_received(key, line, params));
	else if (key == DEL_K)
		back_space(line);
	else if (key == UARROW && params->history)
		return (up_arrow(line, params->history));
	else if (key == DARROW && params->history)
		return (down_arrow(line, params->history));
	else if (key == RARROW || key == LARROW)
		move_key(line, key);
	else if (key == HOME)
		home_key(line);
	else if (key == END)
		end_key(line);
	else if (key == DEL || key == EOF_K)
		del_key(line);
	else if (key == CL_ARROW || key == CR_ARROW)
		move_word(line, key);
	return (1);
}
