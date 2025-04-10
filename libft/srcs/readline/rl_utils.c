/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:13:23 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 12:10:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_readline_params(t_readline *params)
{
	params->prompt = NULL;
	params->history = NULL;
	params->autocomplete = false;
	params->sigint_nl = false;
	params->quit_reason = RL_INVALID;
}

int	reset_line(t_rline*line)
{
	char	*cpy;

	cpy = ft_strdup(line->current_line);
	if (!cpy)
		return (0);
	ft_memset(cpy, '\b', line->cursor);
	write(STDIN_FILENO, cpy, line->cursor);
	ft_memset(cpy, ' ', line->end);
	write(STDIN_FILENO, cpy, line->end);
	ft_memset(cpy, '\b', line->end);
	write(STDIN_FILENO, cpy, line->end);
	free(cpy);
	return (1);
}

void	write_x_times(char *buff, char c, size_t times)
{
	if (!buff)
		return ;
	ft_memset(buff, c, times);
	write(STDIN_FILENO, buff, times);
	return ;
}
