/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 01:36:01 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	open_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_fprintf(2, "Invalid number of arguments !\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strrcmp(av[1], ".ber") != 0)
	{
		ft_fprintf(2, "Invalid format !\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Invalid file !\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_elem_lst	elements;
	int			fd;

	fd = open_file(ac, av);
	if (!new_elem_list(&elements))
		return (close(fd), EXIT_FAILURE);
	// TODO: map file to the elem list and set elem count to 0 to get elems
	clear_arena(&elements.arena);
	close(fd);
	mlx_start(&mlx, 1920, 1080);
	mlx_loop(mlx.mlx);
	return (EXIT_FAILURE);
}
