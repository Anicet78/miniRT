/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:23 by agruet            #+#    #+#             */
/*   Updated: 2025/01/22 11:07:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_normal_chars(const char *s, int *current)
{
	int	start;
	int	len;

	start = *current;
	while (s[*current] && s[*current] != '%')
		(*current)++;
	len = *current - start;
	write(1, &s[start], len);
	return (len);
}

static int	get_conversion(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_len_fd(va_arg(ap, int), 1));
	else if (c == 's')
		return (ft_putstr_len_fd(va_arg(ap, char *), 1));
	else if (c == 'p')
		return (ft_printptr_fd(va_arg(ap, unsigned long long), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base_len_fd(va_arg(ap, int), BASE_10, 10, 1));
	else if (c == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_10, 10, 1));
	else if (c == 'l')
		return (ft_putnbr_long_fd(va_arg(ap, long), 1));
	else if (c == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16L, 16, 1));
	else if (c == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16U, 16, 1));
	else if (c == '%')
		return (ft_putchar_len_fd('%', 1));
	else if (c == 'f')
		return (ft_putnbr_double_fd(va_arg(ap, double), 9, 1));
	else if (c == 0)
		return (0);
	else
		return (ft_putchar_len_fd('%', 1) + ft_putchar_len_fd(c, 1));
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;
	int		current;

	if (!s)
		return (-1);
	va_start(ap, s);
	current = 0;
	len = 0;
	while (s[current])
	{
		if (s[current] == '%')
		{
			len += get_conversion(s[current + 1], ap);
			if (s[current + 1])
				current += 2;
			else
				current += 1;
		}
		else
			len += print_normal_chars(s, &current);
	}
	va_end(ap);
	return (len);
}
