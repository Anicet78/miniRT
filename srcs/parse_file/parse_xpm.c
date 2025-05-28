/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:12:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/28 16:45:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	try_file(char **line, char *folder, size_t tabsize, int index)
{
	char			*path;
	const size_t	len = ft_strlen(line[index]);

	if (tabsize <= index)
		return (0);
	if (len == 0)
		return (2);
	if (line[index][len - 1] == '\n')
		line[index][len - 1] = '\0';
	if (access(line[index], F_OK | R_OK))
		return (2);
	if (ft_strrcmp(line[index], ".xpm"))
		return (3);
	path = realpath(line[index], NULL);
	if (!path)
		return (4);
	if (!ft_strlstr(path, folder, 10))
		return (free(path), 5);
	free(path);
	return (1);
}

int	texture_err(int error, int nb, char *type)
{
	char *temp;
	char *err_msg;

	if (error == 0)
		return (0);
	if (error == 1)
		return (1);
	if (error == 2)
		temp = ft_strdup("Invalid texture file in ");
	else if (error == 3)
		temp = ft_strdup("Invalid texture file format in ");
	else if (error == 4)
		temp = ft_strdup("Memory allocation failed in ");
	else if (error == 5)
		temp = ft_strdup("Texture file isn't in the `textures` folder in ");
	if (!temp)
		return (print_err("Memory allocation failed", nb), 2);
	err_msg = ft_strjoin(temp, type);
	free(temp);
	if (!err_msg)
		return (print_err("Memory allocation failed", nb), 2);
	print_err(err_msg, nb);
	free(err_msg);
	return (2);
}

int	normal_err(int error, int nb, char *type)
{
	char *temp;
	char *err_msg;

	if (error == 0)
		return (0);
	if (error == 1)
		return (1);
	if (error == 2)
		temp = ft_strdup("Invalid texture file in ");
	else if (error == 3)
		temp = ft_strdup("Invalid texture file format in ");
	else if (error == 4)
		temp = ft_strdup("Memory allocation failed in ");
	else if (error == 5)
		temp = ft_strdup("Texture file isn't in the `normals` folder in ");
	if (!temp)
		return (print_err("Memory allocation failed", nb), 2);
	err_msg = ft_strjoin(temp, type);
	if (!err_msg)
		return (print_err("Memory allocation failed", nb), 2);
	print_err(err_msg, nb);
	free(err_msg);
	return (2);
}
