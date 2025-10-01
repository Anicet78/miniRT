/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:41:17 by agruet            #+#    #+#             */
/*   Updated: 2025/10/01 14:49:57 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "vec3.h"

# define PI 3.14159265358979323846264338
# define WIDTH 1920
# define SHININESS 2

typedef struct s_display
{
	int			width;
	int			height;
	double		vp_width;
	double		vp_height;
	float		focal_len;
	t_vec		vp_u;
	t_vec		vp_v;
	t_vec		pix_du;
	t_vec		pix_dv;
	t_point		vp_upleft;
	t_point		pixel00;
	int			i;
	int			j;
}	t_display;

typedef struct s_ray
{
	t_point	p;
	t_vec	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	pos;
	t_vec	dir;
	double	fov;
	bool	declared;
}	t_camera;

#endif
