/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 12:00:49 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mandatory.h"

static int	open_file(int ac, char **av)
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
	t_mandrt	rt;
	t_display	display;
	int			fd;
	bool		map_file;

	fd = open_file(ac, av);
	if (!init_minirt(&rt, fd))
		return (close(fd), EXIT_FAILURE);
	map_file = read_rtfile(fd, &rt.elements, rt.arena);
	close(fd);
	if (!map_file)
		kill_mlx(&rt, EXIT_FAILURE);
	display = init_display(&rt.elements.cam);
	mand_mlx_start(&rt, display.width, display.height);
	// render
	mlx_loop(rt.mlx.mlx);
	return (EXIT_FAILURE);
}
