/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/29 12:17:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	open_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		print_err("Invalid number of arguments !", 0);
		exit(EXIT_FAILURE);
	}
	if (ft_strrcmp(av[1], ".rt") != 0)
	{
		print_err("Invalid format !", 0);
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "\e[1;31mError\n");
		perror(av[1]);
		ft_fprintf(2, "\e[0m");
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
		return (clear_arena(&elements.arena), EXIT_FAILURE);
	else
	{
		ft_printf("\e[1;32mParsing Success !\e[0m\n");
		clear_arena(&elements.arena);
		return (EXIT_FAILURE);
	}
	close(fd);
	mlx_start(&mlx, 1920, 1080);
	clear_arena(&elements.arena);
	ft_printf("wwwwwwwwww\n");
	mlx_loop(mlx.mlx);
	return (EXIT_FAILURE);
}
