/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/06/18 16:15:08 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec3.h"
# include "bvh.h"
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
	int			i;
	int			j;
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
	void	**imgs;
	char	**addr;
	size_t	img_amount;
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
t_elem_lst	*init_minirt(t_rt *rt);

// mlx
void		mlx_start(t_rt *rt, int width, int height);
void		kill_mlx(t_rt *minirt, int exit_code);
void		put_pixel_to_img(t_mlx *mlx, void *addr, uint32_t coords[2], int col);
int			destroy_hook(t_rt *rt);
int			key_hook(int keycode, t_rt *rt);

// tristan
t_display	*init_all_displays(t_camera *cam, t_arena *arena, size_t frame_amount);
t_display	init_display(t_camera *cam);
void		render_display(t_rt *rt, t_display *d);
t_color		white_color();
t_color		surface_color(t_image *texture, double u, double v);
t_color		ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface);
t_color		lambertian(t_hit *hit, t_elem_lst *elems, t_color *surface, size_t frame);

// tests
void		print_ambient(t_ambient *ambient);
void		print_cam(t_camera *camera);
void		print_light(t_light *light);
void		print_sphere(t_sphere *sphere);
void		print_plane(t_plane *plane);
void		print_cylinder(t_cylinder *cylinder);

// bvh
void		create_all_bvh(t_rt *rt);
void		init_builder(t_elem_lst *elems, t_bvh_builder *builder, size_t frame);
size_t		count_elem_amount(t_elem_lst *elems, size_t frame);
// bool		hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit, size_t index);
bool		hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit);
bool		hit_object(void *obj, t_ray *r, t_hit *hit);
bool		hit_aabb(t_aabb *box, t_ray *r);

// utils
uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);
int			print_err(char *msg, int line);
int			frame_err(char *msg, int frame);
void		ft_usleep(size_t usec);
long		get_time(struct timeval *timestamp);
long		get_time_now(void);

// intersects

bool		hit_sphere(t_sphere *sphere, t_ray *r, t_hit *hit);
bool		hit_plane(t_plane *plane, t_ray *r, t_hit *hit);
bool		hit_cylinder(t_cylinder *c, t_ray *r, t_hit *hit);
bool		closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit, size_t frame);
int32_t		ray_to_color(t_ray *r, t_elem_lst *elems, size_t frame);

#endif
