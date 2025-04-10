/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:30 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 11:38:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*history_up(t_dlist **history)
{
	if (!(*history)->next)
		return (NULL);
	*history = (*history)->next;
	return ((*history)->content);
}

char	*history_down(t_dlist **history)
{
	if (!(*history)->prev)
		return (NULL);
	*history = (*history)->prev;
	return ((*history)->content);
}

int	cmd_add_history(t_dlist **history, char *cmd)
{
	t_dlist	*new;
	char	*new_content;
	t_dlist	*search_history;

	if (!history || !*cmd)
		return (1);
	search_history = ft_strstr_dlst(*history, cmd);
	if (search_history)
		return (ft_dlst_shift_up(history, search_history), 1);
	new_content = ft_strdup(cmd);
	if (!new_content)
		return (0);
	new = ft_dlstnew(new_content);
	if (!new)
		return (free(new_content), 0);
	ft_dlstadd_front(history, new);
	return (1);
}
