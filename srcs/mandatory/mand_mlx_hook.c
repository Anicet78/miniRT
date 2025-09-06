/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_mlx_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:47:42 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 18:51:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	mand_kill_mlx(t_mandrt *rt, int exit_code)
{
	if (rt->mlx.img)
		mlx_destroy_image(rt->mlx.mlx, rt->mlx.img);
	if (rt->mlx.mlx_win)
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.mlx_win);
	if (rt->mlx.mlx)
	{
		mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
	}
	if (rt->arena)
		clear_arena(&rt->arena);
	exit(exit_code);
}

int	mand_destroy_hook(t_mandrt *rt)
{
	kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}

int	mand_key_hook(int keycode, t_mandrt *rt)
{
	if (keycode == ESC_K)
		kill_mlx(rt, EXIT_SUCCESS);
	return (0);
}