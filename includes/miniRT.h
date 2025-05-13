/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/05/13 18:31:07 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec3.h"
# include "elements.h"
# include "threads.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdint.h>
# include <fcntl.h>

# define PI 3.14159265358979323846264338
# define WIDTH 1920
# define ASPECT_RATIO (16.0 / 9.0)

# define ESC_K 65307

typedef struct s_display
{
	int			width;
	int			height;
	double		vp_width;
	double		vp_height;
	float		focal_len;
	t_vec		vp_u;
	t_vec		vp_v;
	t_vec		pix_du;
	t_vec		pix_dv;
	t_point		vp_upleft;
	t_point		pixel00;
	uint32_t	i;
	uint32_t	j;
}	t_display;

typedef struct s_ray
{
	t_point	p;
	t_vec	dir;
}	t_ray;

typedef struct s_circle
{
	t_point	p;
	double	rad;
}	t_circle;

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

typedef struct s_miniRT
{
	t_mlx		mlx;
	t_elem_lst	elements;
	t_arena		*arena;
	t_queue		queue;
	pthread_t	*threads;
	uint8_t		thread_amount;
}	t_rt;

typedef struct s_hit
{
	t_point		p;
	t_vec		normal;
	double		t;
	t_material	*mat;
	float		u;
	float		v;
	bool		front;
}	t_hit;

// init
t_elem_lst	*init_elem_list(t_rt *minirt);

// mlx
void		mlx_start(t_rt *minirt, int width, int height);
void		kill_mlx(t_rt *minirt, int exit_code);
void		put_pixel_to_img(t_mlx *img, int x, int y, int color);

// tristan
void		print_color(unsigned int col);
int			min(int a, int b);
int			max(int a, int b);
double		mind(double a, double b);
double		maxd(double a, double b);
t_display	init_display(t_camera *cam);
void		render_display(t_rt *rt, t_display *d);
// anicet
// t_color		ray_color(t_ray *ray);

// tests
void		print_ambient(t_ambient *ambient);
void		print_cam(t_camera *camera);
void		print_light(t_light *light);
void		print_sphere(t_sphere *sphere);
void		print_plane(t_plane *plane);
void		print_cylinder(t_cylinder *cylinder);

// utils
uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);
int			print_err(char *msg, int line);

// intersects

bool	hit_sphere(t_sphere *sphere, t_ray *r, t_hit *hit);
bool	hit_plane(t_plane *plane, t_ray *r, t_hit *hit);
bool	hit_cylinder(t_cylinder *c, t_ray *r, t_hit *hit);
bool	closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit);
int32_t	ray_to_color(t_ray *r, t_elem_lst *elems);

#endif
