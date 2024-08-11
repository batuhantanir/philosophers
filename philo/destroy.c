/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:52:32 by btanir            #+#    #+#             */
/*   Updated: 2024/08/11 10:48:22 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_data(t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->display);
		pthread_mutex_destroy(&data->dead_mtx);
	}
}

void	destroy_fork(t_data *data, pthread_mutex_t *forks, int i)
{
	destroy_data(data);
	while (--i > -1)
		pthread_mutex_destroy(&forks[i]);
}

void	destroy_philo(t_philo *philos, int i)
{
	while (--i > -1)
	{
		pthread_mutex_destroy(&philos[i].philo_last_eat_mutex);
		philos[i].left_fork = NULL;
		philos[i].right_fork = NULL;
	}
}

void	destroy(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	destroy_data(data);
	if (forks)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_destroy(&forks[i]);
			pthread_mutex_destroy(&philos[i].philo_last_eat_mutex);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
		}
	}
}
