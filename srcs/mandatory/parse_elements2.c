/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:06 by agruet            #+#    #+#             */
/*   Updated: 2025/09/05 18:09:48 by tgallet          ###   ########.fr       */
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
