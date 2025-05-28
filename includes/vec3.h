/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:38:50 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/28 15:57:33 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <stdint.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_icolor
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	alpha;
}	t_icolor;

typedef t_vec	t_point;
typedef t_vec	t_color;

double		dot(t_vec a, t_vec b);
t_vec		vmul(t_vec a, double scalar);
t_vec		vadd(t_vec a, t_vec b);
double		magn(t_vec a);
t_vec		norm(t_vec a);
t_vec		vsub(t_vec a, t_vec b);
t_vec		vdiv(t_vec a, double scalar);
t_vec		vtrans(t_vec a, double scalar);
t_vec		vmulv(t_vec a, t_vec b);
uint32_t	vec_to_col(t_color a);
t_color		uint_to_tcol(uint32_t col);
t_vec		cross_prod(t_vec a, t_vec b);
t_vec		up_v();
t_vec		right_v();
t_color		lerp_vec(t_color a, t_color b, double t);

#endif
