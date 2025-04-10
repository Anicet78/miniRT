/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/09 16:11:17 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_signals(int sig)
{
	(void)sig;
	return ;
}

void	rl_init_signals(void)
{
	struct sigaction	sa;

	init_sighandler(&sa, &handle_signals);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	rl_reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	rl_signal_received(int key, t_rline *line, t_readline *params)
{
	if (key == FINISH_READING)
	{
		params->quit_reason = RL_FINISHED;
		return (0);
	}
	clear_line(line, params->history, true);
	if (params->sigint_nl == false)
	{
		ft_fprintf(0, "\n");
		params->quit_reason = RL_KILLED;
		return (0);
	}
	if (params->autocomplete == true && line->dir)
		closedir(line->dir);
	if (!new_buffer(line, params))
		return (0);
	if (isatty(STDIN_FILENO))
		ft_fprintf(STDIN_FILENO, "\n%s", params->prompt);
	return (1);
}
