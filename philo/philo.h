/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:34:40 by btanir            #+#    #+#             */
/*   Updated: 2024/08/09 19:00:59 by btanir           ###   ########.fr       */
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
	pthread_mutex_t	dead_mtx;
}					t_data;

typedef struct s_philo
{
	int				philo_index;
	int				philo_loop;
	long long		philo_start;
	long long		philo_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_last_eat_mutex;
	pthread_t		philo_thread;
	t_data			*data;
}					t_philo;

# define SUCCESS 0
# define FAILURE 1
# define ARGS_ERR "Invalid arguments"
# define MUTEX_ERR "Failed to initialize mutex"
# define ALLOCATION_ERR "malloc() failed to allocate memory"
# define CREATE_ERR "Failed to create a thread"
# define JOIN_ERR "Failed to join a thread"

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

int					arg_control(int argc, char **argv);
int					control_data(t_data *data);
int					init_data(t_data *data, char **argv);
long				ft_atol(const char *str);
int					ft_isdigit(int c);
pthread_mutex_t		*init_forks(t_data *data);
long long			get_time(void);
t_philo				*init_philo(t_data *data, pthread_mutex_t *forks);
int					start_sim(t_data *data, t_philo *philo);
void				ft_usleep(int wait_time);
void				display(t_philo *philo, char *msg);
void				destroy(t_data *data, pthread_mutex_t *forks,
						t_philo *philos);
void				stalker(t_philo *philo, t_data *data);
#endif
