/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 19:30:29 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mandatory.h"

static t_mandlst	*init_mandrt(t_mandrt *rt, int fd)
{
	rt->mlx.mlx_win = NULL;
	rt->mlx.img = NULL;
	rt->mlx.addr = NULL;
	rt->elements.lst_size = 0;
	rt->elements.lst_count = 0;
	rt->elements.allocated_size = calc_arena_size(fd);
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
	t_mandrt	rt;
	t_display	display;
	int			fd;
	bool		map_file;

	fd = open_file(ac, av);
	if (!init_minirt(&rt, fd))
		return (close(fd), EXIT_FAILURE);
	map_file = mand_parsing(fd, &rt.elements, rt.arena);
	close(fd);
	if (!map_file)
		kill_mlx(&rt, EXIT_FAILURE);
	display = init_display(&rt.elements.cam);
	mand_mlx_start(&rt, display.width, display.height);
	// render
	mlx_loop(rt.mlx.mlx);
	return (EXIT_FAILURE);
}
