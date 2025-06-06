/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3op3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:19 by agruet            #+#    #+#             */
/*   Updated: 2025/06/06 14:49:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	vmin(t_vec a, t_vec b)
{
	return ((t_vec){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)});
}

t_vec	vmax(t_vec a, t_vec b)
{
	return ((t_vec){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)});
}
