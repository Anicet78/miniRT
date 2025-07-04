/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:12 by agruet            #+#    #+#             */
/*   Updated: 2025/06/05 13:20:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_nanosleep(size_t usec)
{
	struct timespec	ts;

	ts.tv_sec = usec / 1000000;
	ts.tv_nsec = (usec % 1000000) * 1000;
	nanosleep(&ts, NULL);
}

void	ft_usleep(size_t usec)
{
	struct timeval	start;
	struct timeval	now;
	long			start_ms;
	long			now_ms;

	gettimeofday(&start, NULL);
	start_ms = get_time(&start) + usec / 1000;
	while (1)
	{
		gettimeofday(&now, NULL);
		now_ms = get_time(&now);
		if (now_ms >= start_ms)
			break;
		usleep(100);
	}
}

long	get_time(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000;
	return (time);
}

long	get_time_now(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (get_time(&timestamp));
}
