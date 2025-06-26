/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/10 14:44:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface)
{
	t_color	color;

	color = hadamar(hit->mat->color, *surface);
	color = hadamar(
		vmul(
			elems->al->color,
			elems->al->ratio
		),
		color
	);
	return (color);
}

t_color	lambertian(t_hit *hit, t_elem_lst *elems, t_color *surface, size_t frame)
{
	t_color	color;
	t_light	*lux;
	size_t	i;

	color = white_color();
	lux = elems->lights[frame];
	i = 0;
	while (lux->declared == true)
	{
		color = hadamar(vmul(vmul(*surface, fmax(0,
			dot(norm(vsub(lux->pos, hit->p)),
			hit->normal))), lux->ratio),color);
		i++;
		lux = elems->lights[frame] + i;
	}
	return (color);
}
