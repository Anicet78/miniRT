/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:43:31 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/10 17:44:09 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vec3.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdint.h>

# define PI 3.14159265358979323846264338
# define WIDTH 500
# define ASPECT_RATIO 1

typedef struct s_ray
{
	t_point	p;
	t_vec	dir;
} t_ray;

typedef struct s_circle
{
	t_point	p;
	double	rad;
}	t_circle;

typedef struct s_display
{
	int		width;
	int		height;
	double	vp_width;
	double	vp_height;
	t_point	camera;
}	t_display;

void	print_color(unsigned int col);
t_display	init_display(double fov, t_point cam);
#endif
