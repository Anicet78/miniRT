/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/05/16 13:08:27 by agruet           ###   ########.fr       */
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

static void	iterate(t_elem_lst *elements, t_arena **arena)
{
	void	*elem;
	int		type;

	elements->count = 0;
	elem = get_next_elem(elements);
	while (elem && elements->count <= elements->frames[0])
	{
		type = get_elem_type(elem);
		if (type == AMBIENT_LIGHTING)
			print_ambient(elem);
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
	t_rt		rt;
	t_display	*display;
	int			fd;
	bool		map_file;

	fd = open_file(ac, av);
	if (!init_elem_list(&rt))
		return (close(fd), EXIT_FAILURE);
	map_file = read_rtfile(fd, &rt.elements, rt.arena);
	close(fd);
	if (!map_file)
		return (clear_arena(&rt.arena), EXIT_FAILURE);
	display = init_all_displays(rt.elements.cam, rt.arena, rt.elements.frame_amount);
	mlx_start(&rt, display[0].width, display[0].height);
	init_queue(&rt);
	init_threads(&rt, display);
	// render_display(&rt, display);
	render_thread(&rt);
	// kill_mlx(&rt, 1);
	mlx_loop(rt.mlx.mlx);
	return (EXIT_FAILURE);
}
