/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:54:10 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:04:53 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Function to simulate the thinking routine of the philosophers.
 * 
 * @param *philos The struct philos.
 */

void	thinking_routine(t_philo *philos)
{
	print_mes(get_time() - philos->table->t_start, THINK, *philos);
	return ;
}

/**
 * Function to simulate the sleep routine of the philosophers.
 * 
 * @param *philos The struct philos.
 */
void	sleep_routine(t_philo *philos)
{
	t_table		*table;

	table = philos->table;
	print_mes(get_time() - table->t_start, SLEEP, *philos);
	ft_usleep(table->t_sleep * 1000);
	thinking_routine(philos);
}

/**
 * Function to simulate the eat routine of the philosophers.
 * 
 * @param *philos The struct philos.
 */
void	eat_routine(t_philo *philos)
{
	t_table		*table;

	table = philos->table;
	pthread_mutex_lock(&philos->table->fork_mutex[philos->r_fork]);
	print_mes(get_time() - philos->table->t_start, R_FORK, *philos);
	pthread_mutex_lock(&philos->table->fork_mutex[philos->l_fork]);
	print_mes(get_time() - philos->table->t_start, L_FORK, *philos);
	pthread_mutex_lock(&philos->check_last_eat);
	philos->t_last_eat = get_time();
	pthread_mutex_unlock(&philos->check_last_eat);
	print_mes(get_time() - table->t_start, EAT, *philos);
	(ft_usleep(table->t_eat * 1000), philos->times_eat++);
	pthread_mutex_lock(&table->all_eat_mutex);
	if (table->n_eat != 0 && table->n_eat == philos->times_eat)
		table->all_eat++;
	pthread_mutex_unlock(&table->all_eat_mutex);
	pthread_mutex_unlock(&philos->table->fork_mutex[philos->r_fork]);
	pthread_mutex_unlock(&philos->table->fork_mutex[philos->l_fork]);
	sleep_routine(philos);
}

/**
 * Function to launch the routines.
 * 
 * @param *args The struct philos passed as a void pointer.
 * 
 * @return It returns NULL when finished.
 */
void	*routine(void *args)
{
	t_philo		*philos;
	t_table		*table;

	philos = (t_philo *)args;
	table = philos->table;
	if (philos->number % 2 == 0)
	{
		pthread_mutex_lock(&table->thread_mutex);
		ft_usleep(1000);
		pthread_mutex_unlock(&table->thread_mutex);
	}
	while (1)
	{
		eat_routine(philos);
		if (!check_death_flag(table))
			break ;
	}
	return (NULL);
}
