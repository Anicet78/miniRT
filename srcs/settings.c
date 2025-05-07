/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:15 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/07 16:16:09 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_display	init_display(double fov, t_point cam)
{
	t_display	ret;

	fov *= PI / 180;
	ret.width = WIDTH;
	ret.height = (int)(WIDTH * (1 / ASPECT_RATIO));
	if (ret.height < 1)
		ret.height = 1;
	ret.vp_width = 2 * tan(fov / 2);
	// ret.vp_width = 2.0;
	ret.vp_height = ret.vp_width * ((double)ret.height / (double)ret.width);
	ret.camera = cam;
	ret.focal_len = ret.width / 2 * tan(fov / 2);
	return (ret);
}
