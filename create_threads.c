/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:56:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:05:02 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* Function to initialize the table struct
*
* @param *array As a parameter it receives the array with the parameters pased
* as argv
*
* @return It returns the struct table
*/
t_table	*init_table(int *array)
{
	t_table	*table;
	int		i;

	i = -1;
	table = malloc(sizeof(t_table));
	table->n_philos = array[1];
	table->t_die = array[2];
	table->t_eat = array[3];
	table->t_sleep = array[4];
	table->death_flag = 0;
	table->all_eat = 0;
	if (array[0] == 6)
		table->n_eat = array[5];
	else
		table->n_eat = 0;
	table->fork_mutex = malloc(table->n_philos * sizeof(pthread_mutex_t));
	pthread_mutex_init(&(table->print_mutex), NULL);
	pthread_mutex_init(&(table->dead_mutex), NULL);
	pthread_mutex_init(&(table->thread_mutex), NULL);
	pthread_mutex_init(&(table->dead_flag_mutex), NULL);
	pthread_mutex_init(&(table->all_eat_mutex), NULL);
	while (++i < table->n_philos)
		pthread_mutex_init(&(table->fork_mutex[i]), NULL);
	table->t_start = get_time();
	return (table);
}

/**
* Function to initialize each philosopher
*
* @param *table As a parameter it receives the struct table
*
* @return It returns the struct philos
*/
t_philo	*create_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(table->n_philos * sizeof(t_philo));
	while (i < table->n_philos)
	{
		philos[i].number = i + 1;
		philos[i].table = table;
		if (i == 0)
			philos[i].l_fork = table->n_philos - 1;
		else
			philos[i].l_fork = i - 1;
		philos[i].r_fork = i;
		philos[i].times_eat = 0;
		pthread_mutex_init(&philos[i].check_last_eat, NULL);
		philos[i].t_last_eat = get_time();
		i++;
	}
	return (philos);
}

/**
* Function to destroy the mutex
*
* @param *philos As a parameter it receives the struct philos
*/
void	ft_destroy_mutex(t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philos->table->print_mutex);
	pthread_mutex_destroy(&philos->table->dead_mutex);
	pthread_mutex_destroy(&philos->table->dead_flag_mutex);
	pthread_mutex_destroy(&philos->table->all_eat_mutex);
	while (++i < philos->table->n_philos)
		pthread_mutex_destroy(&philos->table->fork_mutex[i]);
}

/**
* Function to create the threads
*
* @param *number The number of philosophers
* @param *philos As a parameter it receives the struct philos
*
* @return When finished, it returns 0
*/
int	create_threads(int number, t_philo *philos, t_table *table)
{
	int	i;

	i = -1;
	if (pthread_create(&philos->table->death_thread, NULL, \
	&check_death, (void *)philos))
		return (1);
	pthread_detach(table->death_thread);
	while (++i < number)
	{
		if (pthread_create(&(philos[i].philo_thread),
				NULL, &routine, (void *)&philos[i]))
			return (1);
	}
	i = -1;
	while (++i < number)
	{
		if (pthread_join(philos[i].philo_thread, NULL))
			return (1);
	}
	ft_destroy_mutex(philos);
	return (0);
}
