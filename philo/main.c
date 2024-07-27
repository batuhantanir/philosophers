/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:33:43 by btanir            #+#    #+#             */
/*   Updated: 2024/07/27 15:21:18 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	start_philo(t_data *data)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	forks = init_forks(data);
	if (!forks)
		return (FAILURE);
	philo = init_philo(data, forks);
	if (!philo)
		return (FAILURE);
	free(forks);
	free(philo);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (arg_control(argc, argv) || init_data(&data, argv) || control_data(&data)
		|| start_philo(&data))
		return (FAILURE);
	return (SUCCESS);
}