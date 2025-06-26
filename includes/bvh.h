/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:41:32 by agruet            #+#    #+#             */
/*   Updated: 2025/06/18 15:12:13 by agruet           ###   ########.fr       */
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
	size_t	next;
}	t_bvh_node;

typedef struct s_bvh_builder
{
	t_aabb	bbox;
	void	*obj;
	t_vec	centroid;
}	t_bvh_builder;

typedef struct s_bvh_info
{
	t_arena			*arena;
	t_bvh_builder	*builder;
	t_point			centroid_min;
	t_point			centroid_max;
	size_t			*index_tab;
	size_t			size;
	size_t			*left;
	size_t			left_size;
	size_t			*right;
	size_t			right_size;
	double			cut_pos;
	uint8_t			axis;
	bool			fallback;
}	t_bvh_info;

typedef struct s_bin
{
	t_aabb	bbox;
	size_t	count;
}	t_bin;

// aabb
t_aabb	get_elem_aabb(void *elem);
t_aabb	union_aabb(t_aabb bbox1, t_aabb bbox2);

// bins
void	fill_bins(t_bin *bins, t_bvh_info *info);
int		get_bin_index(double coord, double min_coord, double max_coord, int nbins);
double	surface_area(t_aabb bbox);
uint8_t	cheapest_cut(t_bin *bins, double *out_cost);

// indexs
size_t	*create_first_tab(t_arena *arena, size_t elem_amount);
void	calc_branch_sizes(t_bvh_info *info);
void	create_index_tab(t_bvh_info *info);

// utils
void	calc_centroid(t_bvh_info *info);
void	get_axis(t_bvh_info *info);
void	get_cut_pos(t_bvh_info *info, t_bin *bins);

#endif
