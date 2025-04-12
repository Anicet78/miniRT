/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:32:46 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 01:18:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "miniRT.h"

typedef struct s_elem_lst
{
	t_arena		*arena;
	size_t		capacity;
	size_t		count;
	uintptr_t	*elem_lst;
}	t_elem_lst;

typedef enum elem_type
{
	INVALID,
	CAMERA
}	t_elem_type;

typedef struct s_camera
{
	t_elem_type	type;
	t_point		pos;
}	t_camera;

t_elem_lst	*new_elem_list(t_elem_lst *elements);
t_elem_lst	*add_element(t_elem_lst *elements, void *new_elem, size_t size);

#endif
