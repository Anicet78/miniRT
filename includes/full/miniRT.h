/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/09/08 18:13:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../common/libft.h"
# include "../common/vec3.h"
# include "bvh.h"
# include "../common/display.h"
# include "elements.h"
# include "threads.h"
# include "../../mlx/mlx.h"
# include <math.h>
# include <stdint.h>
# include <fcntl.h>

# define PI 3.14159265358979323846264338
# define WIDTH 1920
# define BUMP_POWER 20

# define ESC_K 65307

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
t_elem_lst	*init_minirt(t_rt *rt, int fd);

// mlx
void		mlx_start(t_rt *rt, int width, int height);
void		kill_mlx(t_rt *minirt, int exit_code);
void		put_pixel_to_img(t_mlx *mlx, void *addr,
				uint32_t coords[2], int col);
int			destroy_hook(t_rt *rt);
void		destroy_threads(t_rt *rt);
void		destroy_mlx(t_rt *rt);
int			key_hook(int keycode, t_rt *rt);
int			loop_hook(t_rt *rt);

// tristan
t_display	*init_all_displays(t_camera *cam, t_arena *arena,
				size_t frame_amount);
t_display	init_display(t_camera *cam);
t_color		surface_color(t_image *texture, double u, double v);
t_color		ambient_component(t_hit *hit, t_elem_lst *elems, t_color *surface);
t_color		diffuse_specular(t_hit *hit, t_elem_lst *elems,
				t_color *surface, size_t frame);
void		bump_mapping(t_hit *hit);

// bvh
void		create_all_bvh(t_rt *rt);
void		init_builder(t_elem_lst *elems, t_bvh_builder *builder,
				size_t frame);
size_t		count_elem_amount(t_elem_lst *elems, size_t frame);
bool		hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit);
bool		shadow_hit_bvh(t_bvh_node *bvh, t_ray *r, t_hit *hit);
bool		hit_object(void *obj, t_ray *r, t_hit *hit);
bool		hit_aabb(t_aabb *box, t_ray *r);

// utils
uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);
int			print_err(char *msg, int line);
int			frame_err(char *msg, int frame);
void		ft_nanosleep(size_t usec);
void		ft_usleep(size_t usec);
long		get_time_now(void);
long		get_utime(struct timeval *timestamp);
long		get_utime_now(void);
size_t		calc_arena_size(int fd);

// intersects
bool		hit_sphere(t_sphere *sphere, t_ray *r, t_hit *hit);
bool		hit_plane(t_plane *plane, t_ray *r, t_hit *hit);
bool		hit_cylinder(t_cylinder *c, t_ray *r, t_hit *hit);
bool		hit_cone(t_cone *cone, t_ray *r, t_hit *hit);
bool		closest_hit(t_ray *r, t_elem_lst *elems, t_hit *hit, size_t frame);
int32_t		ray_to_color(t_ray *r, t_elem_lst *elems, size_t frame);

// render
void		realtime_rendering(t_rt *rt, size_t *last_frame,
				long *last_frame_time);
void		pre_rendering(t_rt *rt, long *last_frame_time);
double		wait_framerate(double fps, long last_frame_time);
void		print_fps(t_mlx *mlx, double fps);

#endif
