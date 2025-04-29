/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/29 17:14:19 by agruet           ###   ########.fr       */
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
		print_err(strerror(errno), 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	t_miniRT	minirt;
	int			fd;
	void		*elem;
	bool		map_file;

	fd = open_file(ac, av);
	if (!new_elem_list(&minirt.elements))
		return (close(fd), EXIT_FAILURE);
		minirt.elements.count = 0;
	map_file = read_rtfile(fd, &minirt.elements);
	close(fd);
	if (!map_file)
		return (clear_arena(&minirt.elements.arena), EXIT_FAILURE);
	/* else
	{
		ft_printf("\e[1;32mParsing Success !\e[0m\n");
		clear_arena(&miniRT.elements.arena);
		return (EXIT_FAILURE);
	} */
	mlx_start(&minirt, 1920, 1080);
	mlx_loop(minirt.mlx.mlx);
	return (EXIT_FAILURE);
}
