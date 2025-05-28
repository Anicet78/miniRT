/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:09 by agruet            #+#    #+#             */
/*   Updated: 2025/05/28 17:52:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	add_texture(t_elem_lst *elems, char *filename)
{
	char	*file;
	char	path[PATH_MAX];

	realpath(filename, path);
	file = ft_strrstr(path, "/textures/");
	elems->textures[elems->texture_index++] = get_img(file);
	if (!)
}
