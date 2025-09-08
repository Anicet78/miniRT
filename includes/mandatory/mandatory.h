/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:27:26 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 14:17:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_H
# define MANDATORY_H

# include "libft.h"
# include "vec3.h"
# include "display.h"
# include "../../mlx/mlx.h"
# include <math.h>
# include <stdint.h>
# include <fcntl.h>

# define ESC_K 65307

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

// elements
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

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
	bool	declared;
}	t_ambient;

typedef struct s_light
{
	float	ratio;
	t_point	pos;
	t_color	color;
	bool	declared;
}	t_light;

typedef struct s_sphere
{
	uint8_t		type;
	float		radius;
	t_point		pos;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	uint8_t		type;
	t_color		color;
	t_point		pos;
	t_vec		normal;
}	t_plane;

typedef struct s_cylinder
{
	uint8_t		type;
	t_color		color;
	t_point		pos;
	t_vec		axis;
	float		radius;
	float		height;
}	t_cylinder;

typedef struct s_elem_lst
{
	t_camera	cam;
	t_ambient	amb;
	t_light		light;
	void		*mlx_ptr;
	size_t		allocated_size;
	size_t		count;
	size_t		size;
	uintptr_t	*elem_lst;
}	t_elem_lst;

// render
typedef struct s_hit
{
	t_point		p;
	t_vec		normal;
	double		t;
	t_color		*color;
	float		u;
	float		v;
	bool		front;
}	t_hit;

// miniRT
typedef struct s_miniRT
{
	t_mlx		mlx;
	t_elem_lst	elements;
	t_arena		*arena;
}	t_rt;

// element list
t_elem_lst	*add_element(t_elem_lst *elements, void *new_elem, size_t size);
uint8_t		get_elem_type(void *elem);
size_t		get_elem_size(void *elem);
void		*get_next_elem(t_elem_lst *elements);

// parsing
bool		mand_parsing(int fd, t_elem_lst *elements, t_arena *arena);
t_color		get_color(char *str);
bool		is_color(char *str);
bool		is_vec(char *str);
bool		is_normalize_vec(char *str);
t_point		get_vec(char *str);
double		ft_atof_parse(char *str);
char		**ft_arena_split(char const *s, char c, t_arena *arena);
bool		parse_ambient(t_elem_lst *elements, char **line, int nb);
bool		parse_camera(t_elem_lst *elements, char **line, int nb);
bool		parse_light(t_elem_lst *elements, char **line, int nb);
bool		parse_sphere(t_elem_lst *elements, char **line, int nb);
bool		parse_plane(t_elem_lst *elements, char **line, int nb);
bool		parse_cylinder(t_elem_lst *elements, char **line, int nb);
void		add_ambient_lighting(t_elem_lst *elems, float ratio, t_color col);
void		add_camera(t_elem_lst *elems, t_point p, t_vec axis, uint32_t fov);
void		add_light(t_elem_lst *elems, t_point p, float ratio, t_color col);
bool		add_sphere(t_elem_lst *elems, char **line);
bool		add_plane(t_elem_lst *elems, char **line);
bool		add_cylinder(t_elem_lst *elems, char **line);

// render
t_display	init_display(t_camera *cam);
void		render(t_rt *rt, t_display *d);

// mlx
void		mlx_start(t_rt *rt, int width, int height);
void		kill_mlx(t_rt *rt, int exit_code);
void		put_pixel_to_img(t_mlx *mlx, int x, int y, int color);

// error
int			print_err(char *msg, int line);
int			frame_err(char *msg, int line);

#endif