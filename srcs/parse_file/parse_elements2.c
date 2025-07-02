/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/05/29 17:16:33 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_cylinder(t_elem_lst *elems, char **line, int nb)
{
	const size_t	tsize = tab_len(line);
	int				text;
	int				normal;
	double			height;
	double			diameter;

	if (tsize < 6 || tsize > 8)
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	if (is_vec(line[1]) == false)
		return (print_err("Invalid coordinates in `cylinder`", nb));
	if (is_normalize_vec(line[2]) == false)
		return (print_err("Invalid axis vector in `cylinder`", nb));
	diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `cylinder`", nb));
	height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (print_err("Invalid height in `cylinder`", nb));
	if (is_color(line[5]) == false)
		return (print_err("Invalid color in `cylinder`", nb));
	text = texture_err(try_file(line, "/textures/", tsize, 6), nb, "`cylinder`");
	if (text > 1)
		return (false);
	normal = normal_err(try_file(line, "/normals/", tsize, 6 + text),
		nb, "`cylinder`");
	if (normal > 1)
		return (false);
	if ((tsize > 6 && !normal && !text) || (tsize > 7 && normal + text != 2))
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	return (add_cylinder(elems, line, text, normal));
}

bool	parse_new_frame(t_elem_lst *elems, char **line, int nb)
{
	uint32_t	count;

	if (line[1])
		return (print_err("Invalid amount of argument in `new frame`", nb));
	count = 0;
	while (line[0][count] && line[0][count] == '=')
		count++;
	if (line[0][count] && line[0][count] != '=' && line[0][count] != '\n')
		return (print_err("Invalid argument `new frame`", nb));
	elems->frames[elems->frame_amount] = elems->count;
	elems->frame_amount++;
	elems->light_index = 0;
	return (true);
}

bool	parse_goto(t_elem_lst *elems, char **line, int nb)
{
	size_t	n;
	int		i;

	n = 0;
	if (line[1] && line[2])
		return (print_err("Invalid amount of argument in `goto frame`", nb));
	i = 0;
	while (line[0][i] == '^')
		i++;
	if (line[0][i] != '\0')
		return (print_err("Unknown character in `goto frame`", nb));
	if (line[1])
		n = ft_atol(line[1]);
	else
		n = 1;
	if (n <= 0 || n > elems->frame_amount + 1)
		return (print_err("Invalid frame in `goto frame`", nb));
	i = 0;
	while (line[1] && ft_isdigit(line[1][i]))
		i++;
	if (line[1] && line[1][i] != '\0')
		return (print_err("Invalid frame in `goto frame`", nb));
	elems->loop = n;
	elems->loop_index = elems->frame_amount + 1;
	return (true);
}
