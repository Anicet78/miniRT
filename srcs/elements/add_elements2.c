/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/05/19 13:41:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	add_cylinder(t_elem_lst *elems, t_cylinder *cylinder)
{
	if (!add_element(elems, cylinder, sizeof(t_cylinder)))
		return (false);
	return (true);
}
