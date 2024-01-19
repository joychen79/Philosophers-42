/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:51:20 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:04:57 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Function to free everythng at the end
 *
 * @param *input_array The array with the arguments as *int
 * @param *table Second parameter passed to the function. The Table struct
 * 
 */
void	ft_free(int *input_array, t_philo *philos, t_table *table)
{
	if (input_array[1] != 1)
	{
		free(table->fork_mutex);
		free(philos);
		free(table);
	}
	free(input_array);
}

/**
 * If there's only one philo, takes one fork and die
 *
 * @param time_die Second parameter passed to the program. The time it takes to
 * the philosopher to die if he has not eaten
 * 
 */
void	ft_one_philo(time_t time_die)
{
	int		philo;
	time_t	t_action;
	time_t	start;

	philo = 1;
	start = get_time();
	t_action = get_time();
	printf("%6ld %3d has taken a fork\n", t_action - start, philo);
	ft_usleep(time_die * 1000);
	t_action = get_time();
	printf("%6ld %3d died\n", t_action - start, philo);
}

/**
 * Main function. Receives argc ang argv, checks the input and inicialices
 * table and philos
 *
 * @param argv The params rececived when launching the program
 * 
 */
int	main(int argc, char *argv[])
{
	int		*input_array;
	t_philo	*philos;
	t_table	*table;

	table = NULL;
	philos = NULL;
	if (argc == 5 || argc == 6)
		input_array = check_input(argc, argv);
	else
	{
		printf("Error in the arguments. You must enter: number_of_philos \n	\
time_to_die time to eat time_to_sleep number_of_times_to_eat (opt)\n");
		exit (1);
	}
	if (input_array[1] == 1)
		ft_one_philo(input_array[2]);
	else
	{
		table = init_table(input_array);
		philos = create_philos(table);
		table->philos = philos;
		create_threads(input_array[1], philos, table);
	}
	ft_free(input_array, philos, table);
	return (0);
}
