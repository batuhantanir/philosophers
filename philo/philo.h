/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:34:40 by btanir            #+#    #+#             */
/*   Updated: 2024/07/27 13:40:20 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>

typedef struct s_data
{
	int				philo_count;
	int				philo_dead;
	int				philo_eat_time;
	int				philo_live_time;
	int				philo_must_eat;
	int				philo_sleep_time;
	pthread_mutex_t	display;
}					t_data;

# define ARGS_ERR "Invalid arguments"
# define MUTEX_ERR "Failed to initialize mutex"

int					arg_control(int argc, char **argv);
int					control_data(t_data *data);
int					init_data(t_data *data, char **argv);
long				ft_atol(const char *str);
int					ft_isdigit(int c);
#endif
