/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:33:03 by btanir            #+#    #+#             */
/*   Updated: 2024/08/09 18:28:52 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(int argc, char **argv)
{
	int	i;
	int	j;

	if ((argc < 5 || argc > 6) && printf("%s\n", ARGS_ERR))
		return (1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]) && printf("%s\n", ARGS_ERR))
				return (1);
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atol(argv[1]);
	if (data->philo_count < 1 && printf("%s\n", ARGS_ERR))
		return (1);
	data->philo_live_time = ft_atol(argv[2]);
	data->philo_eat_time = ft_atol(argv[3]);
	data->philo_sleep_time = ft_atol(argv[4]);
	data->philo_dead = 0;
	if (argv[5])
		data->philo_must_eat = ft_atol(argv[5]);
	else
		data->philo_must_eat = -1;
	if (pthread_mutex_init(&data->display, NULL) && printf("%s\n", MUTEX_ERR))
		return (1);
	if (pthread_mutex_init(&data->dead_mtx, NULL) && printf("%s\n", MUTEX_ERR))
		return (1);
	return (0);
}

int	control_data(t_data *data)
{
	if (data->philo_count < 1 && printf("%s\n", ARGS_ERR))
		return (1);
	if (data->philo_live_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	if (data->philo_eat_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	if (data->philo_sleep_time < 60 && printf("%s\n", ARGS_ERR))
		return (1);
	if (data->philo_must_eat == 0)
		return (1);
	return (0);
}
