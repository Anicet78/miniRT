/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/04/30 14:38:37 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

static void	iterate(t_elem_lst *elements)
{
	void	*elem;
	int		type;

	elements->count = 0;
	elem = get_next_elem(elements);
	while (elem)
	{
		type = get_elem_type(elem);
		if (type == AMBIENT_LIGHTING)
			print_ambient(elem);
		else if (type == CAMERA)
			print_cam(elem);
		else if (type == LIGHT)
			print_light(elem);
		else if (type == SPHERE)
			print_sphere(elem);
		else if (type == PLANE)
			print_plane(elem);
		else if (type == CYLINDER)
			print_cylinder(elem);
		elem = get_next_elem(elements);
	}
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
	iterate(&minirt.elements);
	mlx_loop(minirt.mlx.mlx);
	return (EXIT_FAILURE);
}
