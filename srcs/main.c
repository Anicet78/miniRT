/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 21:07:23 by agruet           ###   ########.fr       */
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
	if (ft_strrcmp(av[1], ".rt") != 0)
	{
		ft_fprintf(2, "Invalid format !\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
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
	void		*elem;

	fd = open_file(ac, av);
	if (!new_elem_list(&elements))
		return (close(fd), EXIT_FAILURE);
	add_ambient_lighting(&elements, 12.0, 50);
	elements.count = 0;
	// mlx_start(&mlx, 1920, 1080);
	clear_arena(&elements.arena);
	close(fd);
	// mlx_loop(mlx.mlx);
	return (EXIT_FAILURE);
}
