/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:09 by agruet            #+#    #+#             */
/*   Updated: 2025/07/16 16:27:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_image	*add_img(char *file[2], t_image *list, size_t amount, void *mlx_ptr)
{
	size_t	i;
	t_image	*image;
	char	*name;

	i = 0;
	name = file[0];
	while (i < amount && list[i].declared && ft_strcmp(list[i].name, name))
		i++;
	if (i >= amount)
		return (NULL);
	image = &list[i];
	if (list[i].declared == true)
		return (image);
	image->name = name;
	image->img = mlx_xpm_file_to_image(mlx_ptr, file[1],
			&image->width, &image->height);
	if (!image->img)
		return (NULL);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	if (!image->addr)
		return (NULL);
	image->declared = true;
	return (image);
}

t_image	*add_texture(t_elem_lst *elems, char *filename)
{
	char	*file;

	file = ft_strrchr(filename, '/');
	if (!file)
		return (NULL);
	file++;
	return (add_img((char *[2]){file, filename}, elems->textures,
		elems->texture_amount, elems->mlx_ptr));
}

t_image	*add_normal(t_elem_lst *elems, char *filename)
{
	char	*file;

	file = ft_strrchr(filename, '/');
	if (!file)
		return (NULL);
	file++;
	return (add_img((char *[2]){file, filename},
		elems->normals, elems->normal_amount, elems->mlx_ptr));
}
