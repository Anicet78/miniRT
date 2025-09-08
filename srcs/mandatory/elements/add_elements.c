/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:11:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mandatory.h"

void	add_ambient_lighting(t_elem_lst *elems, float ratio, t_color color)
{
	elems->amb.ratio = ratio;
	elems->amb.color = color;
	elems->amb.declared = true;
}

void	add_camera(t_elem_lst *elems, t_point pos, t_vec axis, uint32_t fov)
{
	elems->cam.pos = pos;
	elems->cam.dir = axis;
	elems->cam.fov = fov;
	elems->cam.declared = true;
}

void	add_light(t_elem_lst *elems, t_point pos, float ratio, t_color color)
{
	elems->light.ratio = ratio;
	elems->light.pos = pos;
	elems->light.color = color;
	elems->light.declared = true;
}

bool	add_sphere(t_elem_lst *elems, char **line)
{
	t_sphere	sp;

	sp.type = SPHERE;
	sp.radius = ft_atof(line[2]) / 2;
	sp.pos = get_vec(line[1]);
	sp.color = get_color(line[3]);
	if (!add_element(elems, &sp, sizeof(t_sphere)))
		return (false);
	return (true);
}

bool	add_plane(t_elem_lst *elems, char **line)
{
	t_plane	pl;

	pl.type = PLANE;
	pl.pos = get_vec(line[1]);
	pl.normal = norm(get_vec(line[2]));
	pl.color = get_color(line[3]);
	if (!add_element(elems, &pl, sizeof(t_sphere)))
		return (false);
	return (true);
}
