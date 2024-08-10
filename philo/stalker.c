/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stalker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:40:46 by btanir            #+#    #+#             */
/*   Updated: 2024/08/10 11:19:34 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo_stalker(t_data *data, t_philo *philo)
{
	if (data->philo_count == 1)
	{
		pthread_mutex_lock(&philo->philo_last_eat_mutex);
		if ((get_time()
				- philo->philo_last_eat) >= philo->data->philo_live_time)
		{
			display(&philo[0], DEAD);
			pthread_mutex_lock(&philo->data->dead_mtx);
			philo->data->philo_dead = 1;
			pthread_mutex_unlock(&philo->data->dead_mtx);
			pthread_mutex_unlock(&philo->philo_last_eat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->philo_last_eat_mutex);
		return (1);
	}
	return (0);
}

static int	check_stalker(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].philo_last_eat_mutex);
	if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
	{
		pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
		return (1);
	}
	if ((get_time()
			- philo[i].philo_last_eat) >= philo[i].data->philo_live_time)
	{
		display(&philo[i], DEAD);
		pthread_mutex_lock(&philo[i].data->dead_mtx);
		philo[i].data->philo_dead = 1;
		pthread_mutex_unlock(&philo[i].data->dead_mtx);
		pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
	return (0);
}

void	stalker(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (one_philo_stalker(data, philo))
		return ;
	while (1)
	{
		if (i < data->philo_count)
			i = 0;
		if (check_stalker(philo, i))
			break ;
		i++;
	}
}
