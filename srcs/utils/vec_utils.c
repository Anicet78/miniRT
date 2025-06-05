/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:03:17 by tgallet           #+#    #+#             */
/*   Updated: 2025/06/05 13:20:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"

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
