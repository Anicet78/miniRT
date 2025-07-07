/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:12 by agruet            #+#    #+#             */
/*   Updated: 2025/07/07 11:45:27 by agruet           ###   ########.fr       */
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
	start_ms = get_utime(&start) + usec;
	while (1)
	{
		gettimeofday(&now, NULL);
		now_ms = get_utime(&now);
		if (now_ms >= start_ms)
			break;
		usleep(100);
	}
}

long	get_time_now(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

long	get_utime(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000000 + timestamp->tv_usec;
	return (time);
}

long	get_utime_now(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (get_utime(&timestamp));
}
