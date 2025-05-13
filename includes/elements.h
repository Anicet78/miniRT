/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:32:46 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 05:07:35 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "miniRT.h"
# include "vec3.h"
# include <float.h>

typedef enum elem_type
{
	INVALID_ELEM,
	AMBIENT_LIGHTING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_elem_type;

typedef struct s_material
{
	uint32_t	color;
	void		*texture;
	void		*bump;
}	t_material;

typedef struct s_ambient
{
	t_elem_type	type;
	float		ratio;
	uint32_t	color;
}	t_ambient;

typedef struct s_camera
{
	t_point		pos;
	t_vec		dir;
	double		fov;
	bool		declared;
}	t_camera;

typedef struct s_light
{
	t_elem_type	type;
	float		ratio;
	t_point		pos;
	uint32_t	color;
}	t_light;

typedef struct s_sphere
{
	t_elem_type	type;
	float		radius;
	t_point		pos;
	t_material	*mat;
	// uint32_t	color;
}	t_sphere;

typedef struct s_plane
{
	t_elem_type	type;
	t_material	*mat;
	// uint32_t	color;
	t_point		pos;
	t_vec		normal;
}	t_plane;

typedef struct s_cylinder
{
	t_elem_type	type;
	t_material	*mat;
	// uint32_t	color;
	t_point		pos;
	t_vec		axis;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_elem_lst
{
	t_arena		*arena;
	size_t		capacity;
	size_t		count;
	t_camera	cam;
	uintptr_t	*elem_lst; // mettre en char[] pour le foutre dans la stack ?
}	t_elem_lst;

// element list
t_elem_lst	*new_elem_list(t_elem_lst *elements);
t_elem_lst	*add_element(t_elem_lst *elements, void *new_elem, size_t size);
t_elem_type	get_elem_type(void *elem);
size_t		get_elem_size(void *elem);
void		*get_next_elem(t_elem_lst *elements);

// add element functions
t_ambient	*add_ambient_lighting(t_elem_lst *elements, float ratio,
				uint32_t color);
t_camera	*add_camera(t_elem_lst *elements, t_point pos, t_vec axis,
				uint32_t fov);
t_light		*add_light(t_elem_lst *elements, t_point pos, float ratio,
				uint32_t color);
t_sphere	*add_sphere(t_elem_lst *elements, t_point pos, float diameter,
				uint32_t color);
t_plane		*add_plane(t_elem_lst *elements, t_point pos, t_vec axis,
				uint32_t color);
t_cylinder	*add_cylinder(t_elem_lst *elements, t_cylinder *cylinder);

// parsing
bool		read_rtfile(int fd, t_elem_lst *elements);
uint32_t	get_color(char *str);
bool		is_color(char *str);
bool		is_vec(char *str);
bool		is_normalize_vec(char *str);
t_point		get_vec(char *str);
bool		parse_ambient(t_elem_lst *elements, char **line, int nb);
bool		parse_camera(t_elem_lst *elements, char **line, int nb);
bool		parse_light(t_elem_lst *elements, char **line, int nb);
bool		parse_sphere(t_elem_lst *elements, char **line, int nb);
bool		parse_plane(t_elem_lst *elements, char **line, int nb);
bool		parse_cylinder(t_elem_lst *elements, char **line, int nb);
double		ft_atof_parse(char *str);

#endif
