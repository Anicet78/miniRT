/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:46:03 by tgallet           #+#    #+#             */
/*   Updated: 2025/05/10 16:54:21 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	min(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

double	mind(double a, double b)
{
	if (b < a)
		return (b);
	return (a);
}

double	maxd(double a, double b)
{
	if (b > a)
		return (b);
	return (a);
}
