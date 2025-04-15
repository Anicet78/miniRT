/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:25 by agruet            #+#    #+#             */
/*   Updated: 2025/04/15 17:05:05 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder	*add_cylinder(t_elem_lst *elements, t_cylinder *cylinder)
{
	if (!add_element(elements, cylinder, sizeof(t_cylinder)))
		return (NULL);
	return ((t_cylinder *)1);
}
