/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:50:15 by btanir            #+#    #+#             */
/*   Updated: 2024/08/10 11:17:03 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *philos);
static void	one_philo(t_philo *philo);
static void	eat(t_philo *philo);

int	start_sim(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].philo_start = get_time();
		if (pthread_create(&philo[i].philo_thread, NULL, philo_routine,
				&philo[i]) && printf("%s\n", CREATE_ERR))
			return (1);
	}
	stalker(philo, data);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(philo[i].philo_thread, NULL) && printf("%s\n",
				JOIN_ERR))
			return (1);
	return (1);
}

static void	wait_even(t_philo *philo)
{
	if (philo->philo_index % 2 == 0)
	{
		ft_usleep(philo->data->philo_eat_time);
		pthread_mutex_lock(&philo->philo_last_eat_mutex);
		philo->philo_last_eat = get_time();
		pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	}
}

static void	*philo_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->philo_last_eat_mutex);
	philo->philo_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	if (philo->data->philo_count == 1)
		return (one_philo(philo), NULL);
	wait_even(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_mtx);
		if (philo->data->philo_dead)
			return (pthread_mutex_unlock(&philo->data->dead_mtx), NULL);
		if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
			break ;
		pthread_mutex_unlock(&philo->data->dead_mtx);
		eat(philo);
	}
	pthread_mutex_unlock(&philo->data->dead_mtx);
	return (NULL);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo, FORK);
	ft_usleep(philo->data->philo_live_time);
	pthread_mutex_unlock(philo->left_fork);
	display(philo, DEAD);
	return ;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	display(philo, FORK);
	display(philo, EATING);
	pthread_mutex_lock(&philo->philo_last_eat_mutex);
	if (philo->data->philo_must_eat)
		philo->philo_loop--;
	philo->philo_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	ft_usleep(philo->data->philo_eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display(philo, SLEEPING);
	ft_usleep(philo->data->philo_sleep_time);
	display(philo, THINKING);
}
