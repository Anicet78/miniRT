/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:27 by agruet            #+#    #+#             */
/*   Updated: 2025/04/10 18:06:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reset_flags(t_printf *ft_print)
{
	ft_print->flags = NO_FLAGS;
	ft_print->padding = 0;
	ft_print->precision = 0;
}

void	start_conversion(t_printf *ft_print, char *str, va_list ap)
{
	ft_print->current += 1;
	if (!parse_flags(ft_print, str, ft_print->current))
	{
		write_to_buff(ft_print, "%", 1);
		reset_flags(ft_print);
		return ;
	}
	if (str[ft_print->current] == 'c')
		write_char(ft_print, va_arg(ap, int));
	else if (str[ft_print->current] == 's')
		write_str(ft_print, va_arg(ap, char *));
	else if (str[ft_print->current] == 'p')
		write_ptr(ft_print, va_arg(ap, unsigned long long));
	else if (str[ft_print->current] == 'd' || str[ft_print->current] == 'i')
		write_int(ft_print, va_arg(ap, int), BASE_10, 10);
	else if (str[ft_print->current] == 'u')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_10, 10);
	else if (str[ft_print->current] == 'x')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_16L, 16);
	else if (str[ft_print->current] == 'X')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_16U, 16);
	else
		write_to_buff(ft_print, "%", 1);
	ft_print->current += 1;
	reset_flags(ft_print);
}
