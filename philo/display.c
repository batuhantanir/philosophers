/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:58:22 by btanir            #+#    #+#             */
/*   Updated: 2024/07/28 17:58:35 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->display);
	if (philo->data->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->display);
		return ;
	}
	time = get_time() - philo->philo_start;
	printf("%lld %d %s\n", time, philo->philo_index, msg);
	pthread_mutex_unlock(&philo->data->display);
}
