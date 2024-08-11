/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stalker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:40:46 by btanir            #+#    #+#             */
/*   Updated: 2024/08/11 02:00:28 by btanir           ###   ########.fr       */
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
	if (philo->data->philo_must_eat != 0 && philo[i].philo_loop == 0)
	{
		pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
		return (i + 1);
	}
	if ((get_time()
			- philo[i].philo_last_eat) >= philo[i].data->philo_live_time)
	{
		display(&philo[i], DEAD);
		pthread_mutex_lock(&philo[i].data->dead_mtx);
		philo[i].data->philo_dead = 1;
		pthread_mutex_unlock(&philo[i].data->dead_mtx);
		pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo[i].philo_last_eat_mutex);
	return (0);
}

void	stalker(t_philo *philo, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (one_philo_stalker(data, philo))
		return ;
	while (1)
	{
		if (!(i < data->philo_count))
			i = j;
		if (j == data->philo_count)
			break ;
		j = check_stalker(philo, i);
		if (j == -1)
			break ;
		i++;
	}
}
