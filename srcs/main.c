/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:59 by agruet            #+#    #+#             */
/*   Updated: 2025/05/06 17:19:04 by agruet           ###   ########.fr       */
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
	clear_arena(&elements->arena);
}

void	test_display(t_display *display)
{
	const float	focal_lenght = 1.0;
	const t_vec	camera_center = {0, 0, 0};
	const t_vec	viewport_u = (t_vec){display->vp_width, 0, 0};
	const t_vec	viewport_v = (t_vec){0, -display->vp_height, 0};
	const t_vec	pixel_delta_u = vdiv(viewport_u, display->width);
	const t_vec	pixel_delta_v = vdiv(viewport_v, display->height);
	const t_vec	viewport_upper_left = vsub(vsub(camera_center,
				(t_vec){0, 0, focal_lenght}), vsub(vdiv(viewport_u, 2),
				vdiv(viewport_v, 2)));
	const t_vec	pixel00_loc = vmulv(vaddd(viewport_upper_left, 0.5),
			vadd(pixel_delta_u, pixel_delta_v));
	int			j = 0;
	int			i;

	while (j < display->height)
	{
		i = 0;
		while (i < display->width)
		{
			t_vec	pixel_center = vadd(vadd(pixel00_loc, vmul(pixel_delta_u, i)), vmul(pixel_delta_v, j));
            t_vec	ray_direction = vsub(pixel_center, camera_center);
            t_ray	r = {camera_center, ray_direction};

            t_color pixel_color = ray_color(&r);
            print_color(vec_to_intcol(pixel_color));
			i++;
		}
		j++;
	}
}

int	main(int ac, char **av)
{
	t_miniRT	minirt;
	t_display	display;
	int			fd;
	bool		map_file;

	fd = open_file(ac, av);
	if (!new_elem_list(&minirt.elements))
		return (close(fd), EXIT_FAILURE);
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
	display = init_display(minirt.elements.cam.fov, minirt.elements.cam.pos);
	test_display(&display);
	mlx_start(&minirt, display.width, display.height);
	iterate(&minirt.elements);
	mlx_loop(minirt.mlx.mlx);
	return (EXIT_FAILURE);
}
