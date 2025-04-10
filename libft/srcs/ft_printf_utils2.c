/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:20:38 by agruet            #+#    #+#             */
/*   Updated: 2025/01/22 12:45:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

int	ft_putnbr_long_fd(long n, int fd)
{
	static int	result;
	long		nb;

	result = 0;
	if (n < 0)
	{
		nb = -n;
		write(fd, "-", 1);
	}
	else
		nb = n;
	if (nb >= 10)
		ft_putnbr_long_fd(nb / 10, fd);
	nb = nb % 10 + '0';
	write(fd, &nb, 1);
	result++;
	if (n < 0)
		result++;
	return (result);
}

int	ft_putnbr_double_fd(double n, int accuracy, int fd)
{
	int		count;
	long	exponent;

	count = 0;
	if (n < 0 && (long)n == 0)
		count = ft_putchar_len_fd('-', fd);
	count += ft_putnbr_long_fd((long)n, fd);
	write(1, ".", 2);
	count++;
	exponent = 10;
	while (--accuracy > 0)
		exponent *= 10;
	if (n < 0)
		n = -n;
	n *= exponent;
	count += ft_putnbr_long_fd((long)n, fd);
	return (count);
}
