/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:42:37 by agruet            #+#    #+#             */
/*   Updated: 2025/09/05 16:23:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

size_t	get_bvh_size(size_t elem_amount)
{
	size_t	pow2;
	size_t	bvh_node_count;

	if (elem_amount == 1)
		return (1);
	bvh_node_count = 2 * elem_amount - 1;
	pow2 = 1;
	while (pow2 < bvh_node_count)
		pow2 *= 2;
	return (pow2 * 2);
}
