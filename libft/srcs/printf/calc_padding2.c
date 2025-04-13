/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_padding2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:32:38 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 20:36:21 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_ulong_size(t_printf *ft_print, unsigned long nb, int base_len)
{
	long			size;
	long			precision;
	unsigned long	divisor;

	size = 1;
	divisor = 1;
	while (nb / divisor >= (unsigned long)base_len)
	{
		size++;
		divisor *= base_len;
	}
	precision = ft_print->precision;
	if (precision != 0)
		ft_print->precision++;
	if (nb == 0 && ft_print->flags & PRECISION && precision == 0)
		size--;
	ft_print->precision -= size;
	if (size < precision)
		size = precision;
	if (nb != 0 && ft_print->flags & ALTERNATIVE_FORM)
		size += 2;
	return (size);
}

int	calc_long_size(t_printf *ft_print, long n, int base_len)
{
	long			size;
	long			precision;
	unsigned long	nb;
	unsigned long	divisor;

	size = 1;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= (unsigned long)base_len && size++)
		divisor *= base_len;
	precision = ft_print->precision;
	if (precision != 0)
		ft_print->precision++;
	if (n == 0 && ft_print->flags & PRECISION && precision == 0)
		size--;
	ft_print->precision -= size;
	if (size < precision)
		size = precision;
	if (n < 0 || ft_print->flags & SPACE_POSITIVE
		|| ft_print->flags & SHOW_SIGN)
		size++;
	return (size);
}
