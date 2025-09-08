/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 17:04:36 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mandatory.h"

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

static size_t	calc_arena_size(int *fd, const char *filename)
{
	size_t	size;
	char	*gnl;

	size = 1;
	gnl = get_next_line(*fd);
	while (gnl)
	{
		size++;
		free(gnl);
		gnl = get_next_line(*fd);
	}
	close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		print_err(strerror(errno), 0);
		exit(EXIT_FAILURE);
	}
	return (size * sizeof(t_cylinder) * 10);
}

static t_elem_lst	*init_mandrt(t_rt *rt, int *fd, const char *filename)
{
	rt->mlx.mlx = NULL;
	rt->mlx.mlx_win = NULL;
	rt->mlx.img = NULL;
	rt->mlx.addr = NULL;
	rt->elements.cam.declared = false;
	rt->elements.light.declared = false;
	rt->elements.amb.declared = false;
	rt->elements.size = 0;
	rt->elements.count = 0;
	rt->elements.allocated_size = calc_arena_size(fd, filename);
	rt->arena = arena_init(rt->elements.allocated_size);
	if (!rt->arena)
		return (print_err("Memory allocation failed", 0), NULL);
	rt->elements.allocated_size = rt->elements.allocated_size * 90 / 100;
	rt->elements.elem_lst = arena_calloc(rt->arena,
			rt->elements.allocated_size);
	if (!rt->elements.elem_lst)
	{
		clear_arena(&rt->arena);
		print_err("Memory allocation failed", 0);
		return (NULL);
	}
	return (&rt->elements);
}

int	main(int ac, char **av)
{
	t_rt		rt;
	t_display	display;
	int			fd;
	bool		map_file;

	fd = open_file(ac, av);
	if (!init_mandrt(&rt, &fd, av[1]))
		return (close(fd), EXIT_FAILURE);
	map_file = mand_parsing(fd, &rt.elements, rt.arena);
	close(fd);
	if (!map_file)
		kill_mlx(&rt, EXIT_FAILURE);
	display = init_display(&rt.elements.cam);
	mlx_start(&rt, display.width, display.height);
	// render
	mlx_loop(rt.mlx.mlx);
	return (EXIT_FAILURE);
}
