/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:42:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/10 18:17:53 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int	main(void)
// {
// 	t_display	dis;
// 	t_point		up_left;
// 	t_vec		vp_u;
// 	t_vec		vp_v;
// 	t_vec		pix_u;
// 	t_vec		pix_v;
// 	t_vec		pix00_loc;
// 	int			i;
// 	int			j;
// 	t_point		pix_center;
// 	t_vec		ray_direction;

// 	dis = init_display(100.0, (t_point){0, 0, 0});
// 	vp_u = (t_vec){dis.vp_width, 0, 0};
// 	vp_v = (t_vec){0, -dis.vp_height, 0};
// 	pix_u = vdiv(vp_u, dis.width);
// 	pix_v = vdiv(vp_u, dis.height);

// 	up_left = vsub(dis.camera, (t_vec){0, 0, 1});
// 	up_left = vsub(vsub(up_left, vdiv(pix_u, 2)), vdiv(pix_v, 2));
// 	pix00_loc = vadd(up_left, vmul(vadd(pix_u, pix_v), 0.5));
// 	j = 0;
// 	while (j < dis.width)
// 	{
// 		i = 0;
// 		while (i < dis.height)
// 		{
// 			pix_center =
// 			i++;
// 		}
// 		j++;
// 	}
// }
