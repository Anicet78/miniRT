/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/11 15:35:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;
	int		fd;

	if (ac != 2)
	{
		ft_fprintf(2, "Invalid number of arguments !\n");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	// TODO: map file to chained list
	close(fd);
	mlx_start(&mlx, 1920, 1080);
	mlx_loop(mlx.mlx);
	return (EXIT_FAILURE);
}
