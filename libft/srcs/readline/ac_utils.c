/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:09:35 by agruet            #+#    #+#             */
/*   Updated: 2025/03/30 15:20:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_auto_complete(t_rline *line)
{
	line->tab_index = 0;
	line->in_auto = false;
	line->auto_type = DT_UNKNOWN;
	ft_memset(line->searching_dir, 0, 512);
	line->searching_dir[0] = '.';
	line->dir = opendir(line->searching_dir);
}

int	expand_current(int key, t_rline *line, t_readline *params)
{
	line->in_auto = false;
	if (line->auto_type != DT_DIR)
		return (0);
	else if (key == '\n')
		printkey('/', line, params);
	if (key == READ_FAILED)
	{
		while (line->cursor > 0 && line->cursor > line->tab_index)
			back_space(line);
	}
	line->auto_type = DT_UNKNOWN;
	return (1);
}
