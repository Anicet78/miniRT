/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:13:55 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 11:13:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_raw(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	set_dfl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

static int	ctrl_arrow(char *seq)
{
	read(STDIN_FILENO, seq, 3);
	if (seq[2] == 'C')
		return (CR_ARROW);
	if (seq[2] == 'D')
		return (CL_ARROW);
	return (INVALID_SEQ);
}

static int	find_sequence(char *seq)
{
	if (seq[1] == 'A')
		return (UARROW);
	else if (seq[1] == 'B')
		return (DARROW);
	else if (seq[1] == 'C')
		return (RARROW);
	else if (seq[1] == 'D')
		return (LARROW);
	else if (seq[1] == 'H')
		return (HOME);
	else if (seq[1] == 'F')
		return (END);
	else if (seq[1] == '3')
	{
		read(STDIN_FILENO, &seq[1], 1);
		return (DEL);
	}
	else if (seq[1] == '1')
		return (ctrl_arrow(seq));
	return (INVALID_SEQ);
}

int	read_key(void)
{
	char	ch;
	char	seq[3];
	int		read_val;

	read_val = read(STDIN_FILENO, &ch, 1);
	if (read_val == -1)
		return (READ_FAILED);
	if (read_val == 0)
		return (FINISH_READING);
	if (ch == ESC)
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1
			|| read(STDIN_FILENO, &seq[1], 1) != 1)
			return (READ_FAILED);
		if (seq[0] == '[')
			return (find_sequence(seq));
	}
	return (ch);
}
