/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:56:14 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:04:49 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* Function to get the actual time
*
* @return It returns the time in milisecconds
*/
long	get_time(void)
{
	struct timeval	now;
	long			milliseconds;	

	gettimeofday(&now, NULL);
	milliseconds = now.tv_sec * 1000;
	milliseconds += now.tv_usec / 1000;
	return (milliseconds);
}

/**
* Function to make the process sleep
*
* @param u_secs As a parameter it receives the number of microseconds to sleep
*/
void	ft_usleep(int u_secs)
{
	int			m_secs;
	long		start;

	m_secs = u_secs / 1000;
	start = get_time();
	while (get_time() - start < m_secs)
		usleep(100);
	return ;
}
