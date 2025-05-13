/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 04:50:47 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ambient	*add_ambient_lighting(t_elem_lst *elements, float ratio,
	uint32_t color)
{
	t_ambient	al;

	al.type = AMBIENT_LIGHTING;
	al.ratio = ratio;
	al.color = color;
	if (!add_element(elements, &al, sizeof(t_ambient)))
		return (NULL);
	return ((t_ambient *)1);
}

t_camera	*add_camera(t_elem_lst *elements, t_point pos, t_vec axis,
	uint32_t fov)
{
	elements->cam.pos = pos;
	elements->cam.dir = axis;
	elements->cam.fov = fov;
	elements->cam.declared = true;
	return ((t_camera *)1);
}

t_light	*add_light(t_elem_lst *elements, t_point pos, float ratio,
	uint32_t color)
{
	t_light	li;

	li.type = LIGHT;
	li.ratio = ratio;
	li.pos = pos;
	li.color = color;
	if (!add_element(elements, &li, sizeof(t_light)))
		return (NULL);
	return ((t_light *)1);
}

t_sphere	*add_sphere(t_elem_lst *elements, t_point pos, float diameter,
	uint32_t color)
{
	t_sphere	sp;

	sp.type = SPHERE;
	sp.radius = diameter / 2;
	sp.pos = pos;
	sp.mat.color = color;
	if (!add_element(elements, &sp, sizeof(t_sphere)))
		return (NULL);
	return ((t_sphere *)1);
}

t_plane	*add_plane(t_elem_lst *elements, t_point pos, t_vec axis,
	uint32_t color)
{
	t_plane	pl;

	pl.type = PLANE;
	pl.mat.color = color;
	pl.pos = pos;
	pl.normal = axis;
	if (!add_element(elements, &pl, sizeof(t_plane)))
		return (NULL);
	return ((t_plane *)1);
}
