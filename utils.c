/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:05:29 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:05:46 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Complementary function to atoi. It converts the string to a number
 * 
 * @param *str The number, passed as a string.
 * @param neg The sign of the number (-1 or 1).
 * 
 * @return It returns the number without the sign.
 */
long	ft_number(const char *str, int neg)
{
	long int	num;

	num = 0;
	while (*str)
	{
		if (*str > 47 && *str < 58)
		{
			num = (num * 10) + (*str - 48);
			if (num > 2147483648 && neg == -1)
				(printf("Error\nThe number must be an int\n"), exit(-1));
			if (num > 2147483647 && neg == 1)
				(printf("Error\nThe number must be an int\n"), exit(-1));
		}
		else
			(printf("Error\nNot a number\n"), exit(-1));
		str++;
	}
	return (num);
}

/**
 * Function to converta a number passed as a string to a number
 * 
 * @param *str The number, passed as a string.
 * 
 * @return It returns the number.
 */
int	ft_atoi(const char *str)
{
	size_t	num;
	int		neg;

	neg = 1;
	if (*str == '\0')
		(printf("Error\nNot a number\n"), exit(-1));
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			neg *= -1;
		str++;
	}
	if (*str > 47 && *str < 58)
		num = ft_number(str, neg);
	else
		(printf("Error\nNot a number\n"), exit(-1));
	return ((int)num * neg);
}

/**
 * Function to print the messages
 * 
 * @param t_action The time at which the action to be printed takes place.
 * @param message The type of message that must be printed.
 * @param *philos The struct table.
 */
void	print_mes(time_t t_action, enum e_message message, t_philo philos)
{
	pthread_mutex_lock(&(philos.table->print_mutex));
	if (check_death_flag(philos.table) == 0)
	{
		pthread_mutex_unlock(&(philos.table->print_mutex));
		return ;
	}
	if (message == L_FORK)
		printf("%6ld %3d has taken a fork\n", t_action, philos.number);
	else if (message == R_FORK)
		printf("%6ld %3d has taken a fork\n", t_action, philos.number);
	else if (message == EAT)
		printf("%6ld %3d is eating\n", t_action, philos.number);
	else if (message == THINK)
		printf("%6ld %3d is thinking\n", t_action, philos.number);
	else if (message == SLEEP)
		printf("%6ld %3d is sleeping\n", t_action, philos.number);
	pthread_mutex_unlock(&(philos.table->print_mutex));
	return ;
}
