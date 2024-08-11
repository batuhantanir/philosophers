/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:19:20 by btanir            #+#    #+#             */
/*   Updated: 2024/08/11 10:40:10 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atol(argv[1]);
	if (data->philo_count < 1 && printf("%s\n", ARGS_ERR))
		return (1);
	data->philo_live_time = ft_atol(argv[2]);
	if (data->philo_live_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	data->philo_eat_time = ft_atol(argv[3]);
	if (data->philo_eat_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	data->philo_sleep_time = ft_atol(argv[4]);
	if (data->philo_sleep_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	data->philo_dead = 0;
	if (argv[5])
		data->philo_must_eat = ft_atol(argv[5]);
	else
		data->philo_must_eat = -1;
	if (data->philo_must_eat == 0 && printf("%s\n", ARGS_ERR))
		return (1);
	if (pthread_mutex_init(&data->display, NULL) && printf("%s\n", MUTEX_ERR))
		return (1);
	if (pthread_mutex_init(&data->dead_mtx, NULL) && printf("%s\n", MUTEX_ERR))
		return (pthread_mutex_destroy(&data->display), 1);
	return (0);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!forks && printf("%s\n", ALLOCATION_ERR))
		return (NULL);
	data->fork_count = -1;
	while (++data->fork_count < data->philo_count)
		if (pthread_mutex_init(&forks[data->fork_count], NULL) && printf("%s\n",
				MUTEX_ERR))
			return (destroy_fork(data, forks, data->fork_count), free(forks),
				NULL);
	return (forks);
}

t_philo	*init_philo(t_data *data, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philo;

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
			return (destroy_philo(philo, i), free(philo), NULL);
	}
	return (philo);
}
