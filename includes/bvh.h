/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:41:32 by agruet            #+#    #+#             */
/*   Updated: 2025/06/11 18:27:21 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "miniRT.h"

# define NBINS 16

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

typedef struct s_bvh_builder
{
	t_aabb	bbox;
	void	*obj;
	t_vec	centroid;
}	t_bvh_builder;

typedef struct s_bin
{
	t_aabb	bbox;
	int		count;
}	t_bin;

// aabb
t_aabb	get_elem_aabb(void *elem);
t_aabb	union_aabb(t_aabb bbox1, t_aabb bbox2);

// bins
uint8_t	fill_bins(t_bvh_builder *builder, t_bin bins[8], size_t elem_amount);
uint8_t	cheapest_cut(t_bin *bins);

#endif
