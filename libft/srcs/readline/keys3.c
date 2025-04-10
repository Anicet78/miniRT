/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:12:00 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 00:45:15 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	eof_received(t_rline *line, t_readline *params)
{
	write(0, "\n", 1);
	clear_line(line, params->history, true);
	params->quit_reason = RL_FINISHED;
	return (0);
}

void	move_word(t_rline*line, int key)
{
	if (key == CL_ARROW)
	{
		while (line->cursor > 0 && line->current_line[line->cursor - 1] == ' ')
			move_key(line, LARROW);
		while (line->cursor > 0 && line->current_line[line->cursor - 1] != ' ')
			move_key(line, LARROW);
		return ;
	}
	while (line->cursor < line->end && line->current_line[line->cursor] == ' ')
		move_key(line, RARROW);
	while (line->cursor < line->end && line->current_line[line->cursor] != ' ')
		move_key(line, RARROW);
}
