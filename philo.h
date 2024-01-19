/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:50:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 18:50:31 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					number;
	int					l_fork;
	int					r_fork;
	long				times_eat;
	time_t				t_last_eat;
	pthread_t			philo_thread;
	pthread_mutex_t		check_last_eat;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	int					n_philos;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				all_eat;
	time_t				t_start;
	int					n_eat;
	pthread_t			death_thread;
	int					death_flag;
	pthread_mutex_t		thread_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		dead_flag_mutex;
	pthread_mutex_t		all_eat_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*fork_mutex;
	t_philo				*philos;
}	t_table;

enum	e_message
{
	L_FORK,
	R_FORK,
	EAT,
	THINK,
	SLEEP,
	DYE
};

int		*check_input(int argc, char *argv[]);
t_philo	*create_philos(t_table *table);
void	ft_destroy_mutex(t_philo *philos);
t_table	*init_table(int *array);
int		create_threads(int number, t_philo *philos, t_table *table);
void	*check_death(void *args);

void	*routine(void *args);

void	ft_usleep(int secs);
long	get_time(void);

int		ft_atoi(const char *str);
void	print_mes(time_t t_action, enum e_message message, t_philo philos);

int		check_death_flag(t_table *table);
int		check_eat_time(t_philo philos);

void	check_fork(t_philo *philos);
#endif