/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:39:53 by btanir            #+#    #+#             */
/*   Updated: 2024/08/07 10:35:03 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 43 || str[i] == 45))
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		tmp = (tmp * 10) + (str[i++] - 48);
	if ((tmp * sign < -2147483648 || tmp * sign > 2147483647)
		&& printf("Error: Max_integer\n"))
		return (0);
	return (tmp * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((((long long)time.tv_sec) * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int wait_time)
{
	unsigned long long	time;

	time = get_time();
	while (get_time() - time < (unsigned long long)wait_time)
		usleep(100);
}
