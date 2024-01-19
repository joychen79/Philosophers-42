/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:04:28 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:28:18 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Function to check wether the death_flag has changed to 1 (all the philos
 * have eaten all the times)
 * 
 * @param *philos The struct philos.
 * 
 * @return It returns the flag (1 or 0).
 */
int	check_death_flag(t_table *table)
{
	int	check_flag;

	check_flag = 0;
	pthread_mutex_lock(&(table->dead_flag_mutex));
	if (table->death_flag != 1)
		check_flag = 1;
	pthread_mutex_unlock(&(table->dead_flag_mutex));
	pthread_mutex_lock(&table->all_eat_mutex);
	if (check_flag == 1 && table->n_eat != 0
		&& table->all_eat >= table->n_philos)
		check_flag = 0;
	pthread_mutex_unlock(&table->all_eat_mutex);
	return (check_flag);
}

/**
 * Function to check wether the time to die has been exceeded if the philosopher
 * has not eaten.
 * 
 * @param i A counter received form the check_death function.
 * @param *philos The struct philos.
 * 
 * @return 1 if the time has been exceeded, otherwise it returns 0.
 */
int	check_eat_time(t_philo philos)
{
	long	actual;

	actual = get_time();
	if (actual > philos.t_last_eat + philos.table->t_die)
	{
		pthread_mutex_lock(&(philos.table->dead_flag_mutex));
		philos.table->death_flag = 1;
		pthread_mutex_unlock(&(philos.table->dead_flag_mutex));
		ft_usleep(1000);
		printf("%6ld %3d died\n", get_time() - philos.table->t_start, \
			philos.number);
		return (1);
	}
	return (0);
}

/**
 * Function to check if the philosopher has died.
 * 
 * @param i A counter received form the check_death function.
 * @param *philos The struct philos.
 * 
 * @return 1 if the time has been exceeded, otherwise it returns 0.
 */
void	*check_death(void *args)
{
	int			i;
	t_philo		*philos;
	t_table		*table;

	philos = (t_philo *)args;
	table = philos->table;
	i = -1;
	while (check_death_flag(table))
	{
		while (++i < table->n_philos)
		{
			if (check_eat_time(philos[i]))
				return (NULL);
		}
		if (table->death_flag == 1)
			break ;
		i = -1;
		ft_usleep(300);
	}
	return (NULL);
}
