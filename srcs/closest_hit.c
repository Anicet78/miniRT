/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:56:07 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/13 05:28:02 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	closest_hit(t_ray r, t_elem_lst *elems, t_hit *hit)
{
	void	*elem;
	int		type;
	bool	did_hit;

	ft_memset(hit, 0, sizeof(t_hit));
	did_hit = false;
	elem = get_next_elem(elems);
	while (elem)
	{
		type = get_elem_type(elem);
		if (type == AMBIENT_LIGHTING || type == LIGHT || type == CAMERA)
			continue;
		else if (type == SPHERE)
			did_hit |= hit_sphere(elem, r, hit);
		else if (type == PLANE)
			did_hit |= hit_plane(elem, r, hit);
		else if (type == CYLINDER)
			did_hit |= hit_cylinder(elem, r, hit);
		elem = get_next_elem(elems);
	}
	return (did_hit);
}
