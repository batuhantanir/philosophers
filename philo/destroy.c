/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:52:32 by btanir            #+#    #+#             */
/*   Updated: 2024/08/10 10:44:22 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	destroy(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	if (data)
		pthread_mutex_destroy(&data->display);
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
