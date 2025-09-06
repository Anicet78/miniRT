/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:27:26 by agruet            #+#    #+#             */
/*   Updated: 2025/09/06 19:31:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_H
# define MANDATORY_H

# include "miniRT.h"

typedef struct s_mandmlx
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
}	t_mandmlx;

typedef struct s_mandlst
{
	t_camera	cam;
	t_ambient	amb;
	t_light		light;
	void		*mlx_ptr;
	size_t		allocated_size;
	size_t		lst_count;
	size_t		lst_size;
	uintptr_t	*elem_lst;
}	t_mandlst;

typedef struct s_mandRT
{
	t_mandmlx	mlx;
	t_mandlst	elements;
	t_arena		*arena;
}	t_mandrt;

// elems
void		*mand_get_next_elem(t_mandlst *elements);
t_mandlst	*mand_add_element(t_mandlst *elements, void *new_elem, size_t size);

// parsing
bool		mand_parsing(int fd, t_mandlst *elements, t_arena *arena);
bool		mand_parse_ambient(t_mandlst *elements, char **line, int nb);
bool		mand_parse_camera(t_mandlst *elements, char **line, int nb);
bool		mand_parse_light(t_mandlst *elements, char **line, int nb);
bool		mand_parse_sphere(t_mandlst *elements, char **line, int nb);
bool		mand_parse_plane(t_mandlst *elements, char **line, int nb);
bool		mand_parse_cylinder(t_mandlst *elements, char **line, int nb);

// mlx
void		mand_mlx_start(t_mandrt *rt, int width, int height);
void		mand_kill_mlx(t_mandrt *rt, int exit_code);
int			mand_destroy_hook(t_mandrt *rt);
int			mand_key_hook(int keycode, t_mandrt *rt);

// other
int			open_file(int ac, char **av);

#endif