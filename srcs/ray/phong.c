/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:19:34 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/06 17:20:45 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface)
{
	t_color	color;

	color = int_to_tcol(hit->mat->color);
	color = hadamar(color, *surface);
	color = hadamar(
		vmul(
			int_to_tcol(elems->al->color),
			elems->al->ratio
		),
		color
	);
	return (color);
}

t_color	lambertian(t_hit *hit, t_elem_lst *elems, t_color *surface)
{
	t_color	color;
	t_light	*lux;
	int		i;

	color = white_color();
	i = 0;
	while (i < elems->light_index)
	{
		lux = elems->lights[i];
		color = hadamar(vmul(vmul(*surface, maxd(0,
			dot(norm(vsub(lux->pos, hit->p)),
			hit->normal))), lux->ratio),color);
		i++;
	}
	return (color);
}
