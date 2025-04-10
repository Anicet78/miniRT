/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:49:08 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/10 17:38:52 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_color(uint32_t col)
{
	col &= ~(0xFF << 24);
	printf("red:	%d\n", col >> 16);
	printf("green:	%d\n", (col >> 8) & 0xFF);
	printf("blue:	%d\n", (col) & 0xFF);
}
