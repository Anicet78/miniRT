/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 17:04:48 by agruet           ###   ########.fr       */
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
	elements.count = 0;
	if (read_rtfile(fd, &elements) == false)
	{
		ft_printf("\e[1;31mParsing Error !\n");
		return (EXIT_FAILURE);
	}
	else
	{
		ft_printf("\e[1;32mParsing Success !\n");
		return (EXIT_FAILURE);
	}
	close(fd);
	mlx_start(&mlx, 1920, 1080);
	// add elems to list
	clear_arena(&elements.arena);
	ft_printf("wwwwwwwwww\n");
	mlx_loop(mlx.mlx);
	return (EXIT_FAILURE);
}
