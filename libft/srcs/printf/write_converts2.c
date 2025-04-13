/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:14:07 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 20:39:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_luint(t_printf *ft_print, unsigned long nb, char *base, int b_len)
{
	unsigned long	divisor;
	int				calc_size;

	calc_size = calc_ulong_size(ft_print, nb, b_len);
	if (nb == 0)
		ft_print->flags &= ~ALTERNATIVE_FORM;
	if (apply_numeric_flag(ft_print, calc_size, base, false) == -1)
		return ;
	divisor = 1;
	while (nb / divisor >= (unsigned long)b_len)
		divisor *= b_len;
	while (divisor > 0)
	{
		if (ft_print->flags & PRECISION && ft_print->precision <= 0 && nb == 0)
			break ;
		if (write_to_buff(ft_print, &base[nb / divisor % b_len], 1) == -1)
			return ;
		divisor /= b_len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}

void	write_lint(t_printf *ft_print, long n, char *base, int base_len)
{
	unsigned long	nb;
	unsigned long	divisor;
	int				calc_size;

	calc_size = calc_long_size(ft_print, n, base_len);
	if (apply_numeric_flag(ft_print, calc_size, base, n < 0) == -1)
		return ;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= (unsigned long)base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		if (ft_print->flags & PRECISION && ft_print->precision <= 0 && nb == 0)
			break ;
		if (write_to_buff(ft_print, &base[nb / divisor % base_len], 1) == -1)
			return ;
		divisor /= base_len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}
