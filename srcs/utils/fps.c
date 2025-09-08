/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:48:45 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:14:53 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/full/miniRT.h"

double	wait_framerate(double fps, long last_frame_time)
{
	long		now;
	long		elapsed;
	double		duration;

	if (last_frame_time == 0)
		return (fps);
	duration = 1000000.0 / fps;
	now = get_utime_now();
	elapsed = now - last_frame_time;
	if (elapsed < duration)
		ft_usleep(duration - elapsed);
	elapsed = get_utime_now() - last_frame_time;
	if (elapsed > 0)
		return (1000000.0 / (double)elapsed);
	return (fps);
}

void	get_string(char fps_str[15], double fps, int precision)
{
	size_t	i;
	size_t	divisor;

	i = 5;
	divisor = 1;
	while ((long)fps / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		fps_str[i++] = (size_t)fps / divisor % 10 + '0';
		divisor /= 10;
		if (i > 12)
			return ;
	}
	if (i > 12)
		return ;
	fps_str[i++] = '.';
	while (precision-- > 0)
	{
		fps -= (long)fps;
		fps *= 10;
		fps_str[i++] = (size_t)fps + '0';
	}
}

void	print_fps(t_mlx *mlx, double fps)
{
	char	fps_str[15];

	ft_memset(fps_str, 0, 15);
	fps_str[0] = 'F';
	fps_str[1] = 'P';
	fps_str[2] = 'S';
	fps_str[3] = ':';
	fps_str[4] = ' ';
	get_string(fps_str, fps, 2);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20, 15, 0, fps_str);
}
