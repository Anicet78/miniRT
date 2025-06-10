/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:41:32 by agruet            #+#    #+#             */
/*   Updated: 2025/06/06 15:08:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "miniRT.h"

typedef struct s_aabb
{
	t_point	min;
	t_point	max;
}	t_aabb;

typedef struct s_bvh_node
{
	t_aabb	bbox;
	bool	is_leaf;
	union
	{
		struct
		{
			size_t	left;
			size_t	right;
		};
		void	*obj;
	};
}	t_bvh_node;

#endif
