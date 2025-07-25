/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/07/25 12:22:33 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_cylinder(t_elem_lst *elems, char **line, int nb)
{
	auto size_t tsize = tab_len(line);
	if (tsize < 6 || tsize > 8)
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	if (is_vec(line[1]) == false || is_normalize_vec(line[2]) == false)
		return (print_err("Invalid vector in `cylinder`", nb));
	auto double diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `cylinder`", nb));
	auto double height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (print_err("Invalid height in `cylinder`", nb));
	if (is_color(line[5]) == false)
		return (print_err("Invalid color in `cylinder`", nb));
	auto int text = texture_err(try_file(line, "/textures/", tsize, 6),
		nb, "`cylinder`");
	if (text > 1)
		return (false);
	auto int bmap = bmap_err(try_file(line, "/bumps/", tsize, 6 + text),
		nb, "`cylinder`");
	if (bmap > 1)
		return (false);
	if ((tsize > 6 && !bmap && !text) || (tsize > 7 && bmap + text != 2))
		return (print_err("Invalid amount of argument in `cylinder`", nb));
	return (add_cylinder(elems, line, text, bmap));
}

bool	parse_cone(t_elem_lst *elems, char **line, int nb)
{
	auto size_t tsize = tab_len(line);
	if (tsize < 6 || tsize > 8)
		return (print_err("Invalid amount of argument in `cone`", nb));
	if (is_vec(line[1]) == false || is_normalize_vec(line[2]) == false)
		return (print_err("Invalid vector in `cone`", nb));
	auto double diameter = ft_atof_parse(line[3]);
	if (diameter < 0 || diameter > INT_MAX)
		return (print_err("Invalid diameter in `cone`", nb));
	auto double height = ft_atof_parse(line[4]);
	if (height < 0 || height > INT_MAX)
		return (print_err("Invalid height in `cone`", nb));
	if (is_color(line[5]) == false)
		return (print_err("Invalid color in `cone`", nb));
	auto int text = texture_err(try_file(line, "/textures/", tsize, 6),
		nb, "`cone`");
	if (text > 1)
		return (false);
	auto int bmap = bmap_err(try_file(line, "/bumps/", tsize, 6 + text),
		nb, "`cone`");
	if (bmap > 1)
		return (false);
	if ((tsize > 6 && !bmap && !text) || (tsize > 7 && bmap + text != 2))
		return (print_err("Invalid amount of argument in `cone`", nb));
	return (add_cone(elems, line, text, bmap));
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
	if (line[0][i] != '\0' && line[0][i] != '\n')
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
	if (line[1] && line[1][i] != '\0' && line[1][i] != '\n')
		return (print_err("Invalid frame in `goto frame`", nb));
	elems->loop = n;
	elems->loop_index = elems->frame_amount + 1;
	return (true);
}

bool	parse_fps(t_elem_lst *elems, char **line, int nb)
{
	static bool	declared;
	double		fps;
	size_t		i;

	if (declared == true)
		return (print_err("Multiple declaration of `FPS`", nb));
	declared = true;
	if (!line[1] || line[2])
		return (print_err("Invalid amount of argument in `FPS`", nb));
	fps = ft_atof_parse(line[1]);
	if (fps <= 0)
		return (print_err("FPS amount must be positive in `FPS`", nb));
	if (fps > INT_MAX)
		return (print_err("Invalid amount of fps in `FPS`", nb));
	if (fps > 100000)
		return (print_err("Maximum FPS amount is 100 000 in `FPS`", nb));
	i = 0;
	while (ft_isdigit(line[1][i]) || line[1][i] == '.')
		i++;
	if (line[1][i] != '\n' && line[1][i])
		return (false);
	elems->fps = fps;
	return (true);
}
