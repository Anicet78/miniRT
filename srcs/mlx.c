/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:43 by agruet            #+#    #+#             */
/*   Updated: 2025/04/11 15:10:25 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	destroy_hook(t_mlx *mlx)
{
	kill_mlx(mlx, EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		kill_mlx(mlx, EXIT_SUCCESS);
	return (0);
}

void	mlx_start(t_mlx *mlx, int width, int height)
{
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->width = width;
	mlx->height = height;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		kill_mlx(mlx, EXIT_FAILURE);
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->mlx_win)
		kill_mlx(mlx, EXIT_FAILURE);
	mlx->img = mlx_new_image(mlx->mlx, width, height);
	if (!mlx->img)
		kill_mlx(mlx, EXIT_FAILURE);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		kill_mlx(mlx, EXIT_FAILURE);
	mlx_hook(mlx->mlx_win, 17, 1L << 3, &destroy_hook, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, &key_hook, mlx);
}

void	kill_mlx(t_mlx *mlx, int exit_code)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	exit(exit_code);
}
