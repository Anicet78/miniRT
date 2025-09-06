/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:27:26 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 11:59:56 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_H
# define MANDATORY_H

# include "miniRT.h"

typedef struct s_mandmlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_mandmlx;

typedef struct s_mandlst
{
	t_camera	cam;
	t_ambient	amb;
	t_light		light;
	void		*mlx_ptr;
	uintptr_t	*elem_lst;
}	t_mandlst;

typedef struct s_mandRT
{
	t_mandmlx	mlx;
	t_mandlst	elements;
	t_arena		*arena;
}	t_mandrt;


// mlx
void	mand_mlx_start(t_mandrt *rt, int width, int height);
void	mand_kill_mlx(t_mandrt *rt, int exit_code);
int		mand_destroy_hook(t_mandrt *rt);
int		mand_key_hook(int keycode, t_mandrt *rt);

#endif