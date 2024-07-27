/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:19:20 by btanir            #+#    #+#             */
/*   Updated: 2024/07/27 15:24:21 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

pthread_mutex_t	*init_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!forks && printf("%s\n", ALLOCATION_ERR))
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_mutex_init(&forks[i], NULL) && printf("%s\n", MUTEX_ERR))
			return (NULL);
	return (forks);
}

t_philo	*init_philo(t_data *data, pthread_mutex_t *forks)
{
	int i;
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo && printf("%s\n", ALLOCATION_ERR))
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].philo_index = i + 1;
		if (data->philo_must_eat)
			philo[i].philo_loop = data->philo_must_eat;
		else
			philo[i].philo_loop = 0;
		philo[i].philo_last_eat = get_time();
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->philo_count];
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].philo_last_eat_mutex, NULL)
			&& printf("%s\n", MUTEX_ERR))
			return (NULL);
	}
	return (philo);
}