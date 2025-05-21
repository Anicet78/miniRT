/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/21 17:12:14 by agruet           ###   ########.fr       */
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

bool	add_sphere(t_elem_lst *elems, t_point pos, float diameter, uint32_t color)
{
	t_sphere	sp;

	sp.type = SPHERE;
	sp.radius = diameter / 2;
	sp.pos = pos;
	sp.mat.color = color;
	if (!add_element(elems, &sp, sizeof(t_sphere)))
		return (false);
	return (true);
}

bool	add_plane(t_elem_lst *elems, t_point pos, t_vec axis, uint32_t color)
{
	t_plane	pl;

	pl.type = PLANE;
	pl.mat.color = color;
	pl.pos = pos;
	pl.normal = axis;
	if (!add_element(elems, &pl, sizeof(t_plane)))
		return (false);
	return (true);
}
