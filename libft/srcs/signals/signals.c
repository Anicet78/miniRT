/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:59 by agruet            #+#    #+#             */
/*   Updated: 2025/03/24 11:09:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_sigaction(struct sigaction *sa,
	void (*action)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_sigaction = action;
	sa->sa_flags = SA_SIGINFO;
}

void	init_sighandler(struct sigaction *sa, void (*action)(int))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = action;
	sa->sa_flags = 0;
}
