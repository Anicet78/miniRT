/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:52:58 by agruet            #+#    #+#             */
/*   Updated: 2025/05/10 16:35:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	print_pixels(t_params *params, t_mlx *img, uint64_t i)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	pixel_amount;
	uint32_t	width;
	uint32_t	height;

	pixel_amount = params->pixel_amount;
	width = params->width;
	height = params->height;
	y = params->pixel_start / height;
	x = params->pixel_start % height;
	ft_printf("%u,%u\n", x, y);
	while (i < pixel_amount && y < height)
	{
		while (i < pixel_amount && x < width)
		{
			put_pixel_to_img(img, x, y, 0x0);
			i++;
			x++;
		}
		x = 0;
		y++;
	}
}

void	*start_routine(void *params)
{
	print_pixels((t_params *)params, ((t_params *)params)->img, 0);
	return (NULL);
}

bool	init_threads(t_miniRT *minirt)
{
	t_params	*params;
	uint8_t		amount;
	uint8_t		count;

	minirt->thread_amount = amount;
	minirt->threads = arena_alloc(sizeof(pthread_t) * amount, minirt->arena);
	if (!minirt->threads)
		return (false);
	count = 0;
	while (count < amount)
	{
		params = arena_alloc(sizeof(t_params), minirt->arena);
		if (!params)
			return (false); // + close previous threads
		params->elements = &minirt->elements;
		params->img = &minirt->mlx;
		params->width = minirt->mlx.width;
		params->height = minirt->mlx.height;
		if (pthread_create(&minirt->threads[count], NULL, &start_routine, params))
			return (false); // + close previous threads
		count++;
	}
	mlx_put_image_to_window(minirt->mlx.mlx, minirt->mlx.mlx_win, minirt->mlx.img, 0, 0);
}
