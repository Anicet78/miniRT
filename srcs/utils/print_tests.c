/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:52:35 by agruet            #+#    #+#             */
/*   Updated: 2025/05/20 13:46:20 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_ambient(t_ambient *ambient)
{
	ft_printf("%d | %.2f | %#x\n", AMBIENT_LIGHTING, ambient->ratio, ambient->color);
}

void	print_cam(t_camera *camera)
{
	ft_printf("%d | %.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %d\n", CAMERA,
		camera->pos.x, camera->pos.y, camera->pos.z,
		camera->dir.x, camera->dir.y, camera->dir.z, camera->fov);
}

void	print_light(t_light *light)
{
	ft_printf("%d | %.2f,%.2f,%.2f | %.2f | %#x\n", light->type,
		light->pos.x, light->pos.y, light->pos.z, light->ratio, light->color);
}

void	print_sphere(t_sphere *sphere)
{
	ft_printf("%d | %.2f,%.2f,%.2f | %.2f | %#x\n", sphere->type,
		sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->radius);
}

void	print_plane(t_plane *plane)
{
	ft_printf("%d | %.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %#x\n", plane->type,
		plane->pos.x, plane->pos.y, plane->pos.z,
		plane->normal.x, plane->normal.y, plane->normal.z);
}

void	print_cylinder(t_cylinder *cylinder)
{
	ft_printf("%d | %.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %.2f | %.2f | %#x\n", cylinder->type,
		cylinder->pos.x, cylinder->pos.y, cylinder->pos.z,
		cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
		cylinder->radius, cylinder->height);
}
