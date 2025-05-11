/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:03:17 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/11 02:22:09 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"

t_vec	up_v()
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 1;
	ret.z = 0;
	return (ret);
}

t_vec	right_v()
{
	t_vec	ret;

	ret.x = 1;
	ret.y = 0;
	ret.z = 0;
	return (ret);
}
