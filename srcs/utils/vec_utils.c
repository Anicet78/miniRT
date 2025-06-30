/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:03:17 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/11 16:17:23 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec	up_v(void)
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 1;
	ret.z = 0;
	return (ret);
}

t_vec	right_v(void)
{
	t_vec	ret;

	ret.x = 1;
	ret.y = 0;
	ret.z = 0;
	return (ret);
}

t_color	white_color()
{
	return ((t_color){1.0, 1.0, 1.0});
}

t_color	black_color()
{
	return ((t_color){0.0, 0.0, 0.0});
}

void	clamp_color(t_color *col)
{
	col->x = fmin(col->x, 1);
	col->y = fmin(col->y, 1);
	col->z = fmin(col->z, 1);
}
