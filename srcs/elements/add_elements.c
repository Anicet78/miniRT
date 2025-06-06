/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/06/06 17:52:17 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	add_ambient_lighting(t_elem_lst *elems, float ratio, uint32_t color)
{
	elems->al[elems->frame_amount].ratio = ratio;
	elems->al[elems->frame_amount].color = color;
	elems->al[elems->frame_amount].declared = true;
}

void	add_camera(t_elem_lst *elems, t_point pos, t_vec axis, uint32_t fov)
{
	elems->cam[elems->frame_amount].pos = pos;
	elems->cam[elems->frame_amount].dir = axis;
	elems->cam[elems->frame_amount].fov = fov;
	elems->cam[elems->frame_amount].declared = true;
}

bool	add_light(t_elem_lst *elems, t_point pos, float ratio, uint32_t color)
{
	if (!elems->lights || !elems->lights[elems->frame_amount])
		return (false);
	elems->lights[elems->frame_amount][elems->light_index].ratio = ratio;
	elems->lights[elems->frame_amount][elems->light_index].pos = pos;
	elems->lights[elems->frame_amount][elems->light_index].color = color;
	elems->light_index++;
	return (true);
}

bool	add_sphere(t_elem_lst *elems, char **line, int texture, int normal)
{
	t_sphere	sp;

	sp.type = SPHERE;
	sp.radius = ft_atof(line[2]) / 2;
	sp.pos = get_vec(line[1]);
	sp.mat.color = get_color(line[3]);
	sp.mat.texture = NULL;
	sp.mat.normal = NULL;
	if (texture)
	{
		sp.mat.texture = add_texture(elems, line[4]);
		if (!sp.mat.texture)
			return (print_err("Invalid texture file in `sphere`", 0), false);
	}
	if (normal)
	{
		sp.mat.normal = add_normal(elems, line[4 + texture]);
		if (!sp.mat.normal)
			return (print_err("Invalid normal map file in `sphere`", 0), false);
	}
	if (!add_element(elems, &sp, sizeof(t_sphere)))
		return (false);
	return (true);
}

bool	add_plane(t_elem_lst *elems, char **line, int texture, int normal)
{
	t_plane	pl;

	pl.type = PLANE;
	pl.pos = get_vec(line[1]);
	pl.normal = norm(get_vec(line[2]));
	pl.mat.color = get_color(line[3]);
	pl.mat.texture = NULL;
	pl.mat.normal = NULL;
	if (texture)
	{
		pl.mat.texture = add_texture(elems, line[4]);
		if (!pl.mat.texture)
			return (print_err("Invalid texture file in `plane`", 0), false);
	}
	if (normal)
	{
		pl.mat.normal = add_normal(elems, line[4 + texture]);
		if (!pl.mat.normal)
			return (print_err("Invalid normal map file in `plane`", 0), false);
	}
	if (!add_element(elems, &pl, sizeof(t_plane)))
		return (false);
	return (true);
}
