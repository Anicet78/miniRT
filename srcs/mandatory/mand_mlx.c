/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:41:26 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 18:48:28 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	mand_mlx_start(t_mandrt *rt, int width, int height)
{
	t_mandmlx	*mlx;

	mlx = &rt->mlx;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		kill_mlx(rt, EXIT_FAILURE);
	rt->elements.mlx_ptr = mlx->mlx;
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "mimiRT");
	if (!mlx->mlx_win)
		kill_mlx(rt, EXIT_FAILURE);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (!mlx->img)
		kill_mlx(rt, EXIT_FAILURE);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
				&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		kill_mlx(rt, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &mand_destroy_hook, rt);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &mand_key_hook, rt);
}