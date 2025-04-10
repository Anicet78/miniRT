/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:21:42 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 15:39:00 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	new_buffer(t_rline *line, t_readline *params)
{
	t_dlist	*line_history;

	if (!params)
		return (0);
	if (!params->prompt)
		params->prompt = "";
	params->quit_reason = RL_INVALID;
	line->cursor = 0;
	line->size = 1024;
	line->end = 0;
	if (params->autocomplete == true)
		init_auto_complete(line);
	line->current_line = ft_calloc(line->size, sizeof(char));
	if (!line->current_line)
		return (0);
	if (params->history)
	{
		line_history = ft_dlstnew(line->current_line);
		if (!line_history)
			return (free(line->current_line), 0);
		ft_dlstadd_front(params->history, line_history);
	}
	return (1);
}

static void	rl_quit(t_rline *line, t_readline *params)
{
	set_dfl();
	rl_reset_signals();
	if (!line->current_line && params->quit_reason == RL_INVALID)
		params->quit_reason = RL_ALLOC_FAILED;
	if (params->autocomplete == true && line->dir)
		closedir(line->dir);
}

int	line_too_long(t_rline *line, t_dlist **history)
{
	t_dlist	*line_history;

	if (line->end + 5 < line->size)
		return (1);
	clear_line(line, history, false);
	line->current_line = ft_realloc(line->current_line,
			line->size * 2, line->size);
	if (!line->current_line)
		return (0);
	line->size *= 2;
	if (history)
	{
		line_history = ft_dlstnew(line->current_line);
		if (!line_history)
			return (free(line->current_line), 0);
		ft_dlstadd_front(history, line_history);
	}
	return (1);
}

void	clear_line(t_rline *line, t_dlist **history, bool free_current)
{
	ft_dlst_top(history);
	if (history && (*history)->content == line->current_line)
		dlst_remove_node(history, *history, &void_content);
	else if (history && (*history)->content != line->current_line)
		dlst_remove_node(history, *history, &free_content);
	if (free_current)
		free(line->current_line);
}

char	*ft_readline(t_readline *params)
{
	t_rline	line;
	int		key;

	if (!new_buffer(&line, params))
		return (NULL);
	rl_init_signals();
	set_raw();
	if (isatty(STDIN_FILENO))
		ft_fprintf(STDIN_FILENO, "%s", params->prompt);
	while (1)
	{
		key = read_key();
		if (params->autocomplete == true && auto_complete(key, &line, params))
			continue ;
		else if (ft_isprint(key) && printkey(key, &line, params))
			break ;
		else if (!other_key(key, &line, params))
			return (rl_quit(&line, params), NULL);
		if (!line_too_long(&line, params->history))
			return (rl_quit(&line, params), NULL);
	}
	clear_line(&line, params->history, false);
	if (!cmd_add_history(params->history, line.current_line))
		return (rl_quit(&line, params), NULL);
	return (write(0, "\n", 1), rl_quit(&line, params), line.current_line);
}
