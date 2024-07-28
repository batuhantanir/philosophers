/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:50:15 by btanir            #+#    #+#             */
/*   Updated: 2024/07/28 18:07:22 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *philos);
static void	stalker(t_philo *philo);
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
	stalker(philo);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(philo[i].philo_thread, NULL) && printf("%s\n",
				JOIN_ERR))
			return (1);
	return (0);
}

static void	*philo_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->philo_last_eat = get_time();
	if (philo->data->philo_count == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->philo_index % 2 == 0)
	{
		ft_usleep(philo->data->philo_eat_time);
		philo->philo_last_eat = get_time();
	}
	while (!philo->data->philo_dead)
	{
		if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
			break ;
		eat(philo);
	}
	return (NULL);
}

static void	stalker(t_philo *philo)
{
	while (philo->data->philo_dead != 1)
	{
		if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
			break ;
		if ((get_time()
				- philo->philo_last_eat) >= philo->data->philo_live_time)
		{
			display(philo, DEAD);
			philo->data->philo_dead = 1;
			break ;
		}
	}
}

static void	one_philo(t_philo *philo)
{
	display(philo, FORK);
	ft_usleep(philo->data->philo_live_time);
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
	if (philo->data->philo_must_eat)
		philo->philo_loop--;
	pthread_mutex_lock(&philo->philo_last_eat_mutex);
	philo->philo_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	ft_usleep(philo->data->philo_eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display(philo, SLEEPING);
	ft_usleep(philo->data->philo_sleep_time);
	display(philo, THINKING);
}
