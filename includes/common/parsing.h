/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:53:45 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 16:58:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "vec3.h"

t_color	get_color(char *str);
bool	is_color(char *str);
bool	is_vec(char *str);
bool	is_normalize_vec(char *str);
t_point	get_vec(char *str);
double	ft_atof_parse(char *str);

#endif