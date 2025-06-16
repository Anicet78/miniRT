/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:32:46 by agruet            #+#    #+#             */
/*   Updated: 2025/06/16 15:09:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "miniRT.h"
# include <float.h>
# include "../mlx/mlx_int.h"

# define ELEM_LST_SIZE (CHUNK_SIZE * 90 / 100)

typedef struct s_image
{
	char	*name;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	bool	declared;
}	t_image;

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
	t_image		*texture;
	t_image		*normal;
}	t_material;

typedef struct s_ambient
{
	float		ratio;
	uint32_t	color;
	bool		declared;
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
	float		ratio;
	t_point		pos;
	uint32_t	color;
	bool		declared;
}	t_light;

typedef struct s_sphere
{
	uint8_t		type;
	float		radius;
	t_point		pos;
	t_material	mat;
}	t_sphere;

typedef struct s_plane
{
	t_material	mat;
	t_point		pos;
	t_vec		normal;
	bool		declared;
}	t_plane;

typedef struct s_cylinder
{
	uint8_t		type;
	t_material	mat;
	t_point		pos;
	t_vec		axis;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_elem_lst
{
	size_t		count;
	size_t		size;
	t_plane		**planes;
	size_t		plane_index;
	size_t		*frames;
	size_t		frame_amount;
	t_camera	*cam;
	t_ambient	*al;
	t_light		**lights;
	size_t		light_index;
	t_image		*textures;
	size_t		texture_amount;
	t_image		*normals;
	size_t		normal_amount;
	t_bvh_node	**bvh;
	void		*mlx_ptr;
	uintptr_t	*elem_lst;
}	t_elem_lst;

// element list
t_elem_lst	*add_element(t_elem_lst *elements, void *new_elem, size_t size);
uint8_t		get_elem_type(void *elem);
size_t		get_elem_size(void *elem);
void		*get_next_elem(t_elem_lst *elements);

// add element functions
void		add_ambient_lighting(t_elem_lst *elems, float ratio, uint32_t col);
void		add_camera(t_elem_lst *elems, t_point p, t_vec axis, uint32_t fov);
bool		add_light(t_elem_lst *elems, t_point p, float ratio, uint32_t col);
bool		add_sphere(t_elem_lst *elems, char **line, int texture, int norm);
bool		add_plane(t_elem_lst *elems, char **line, int texture, int norm);
bool		add_cylinder(t_elem_lst *elems, char **line, int texture, int norm);

// parsing
bool		read_rtfile(int fd, t_elem_lst *elements, t_arena *arena);
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
bool		parse_new_frame(t_elem_lst *elements, char **line, int nb);
double		ft_atof_parse(char *str);

// xpm
int			try_file(char **line, char *folder, size_t tabsize, int index);
int			texture_err(int error, int nb, char *type);
int			normal_err(int error, int nb, char *type);
t_image		*add_texture(t_elem_lst *elems, char *filename);
t_image		*add_normal(t_elem_lst *elems, char *filename);

#endif
