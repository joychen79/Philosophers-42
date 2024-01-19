/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:03:50 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/19 19:04:05 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Function to check the received parameters and convert them to numbers
 * of the first occurrence, or -1 if it is not found.
 * 
 * @param argc The number of params received.
 * @param argv The params received when calling the program.
 * 
 * @return An array with the params converted to int.
 */
int	*check_input(int argc, char *argv[])
{
	int		count;
	int		iter;
	int		*input_array;

	count = 0;
	iter = 0;
	input_array = malloc((argc) * sizeof(int));
	input_array[0] = argc;
	while (++count < argc)
	{
		input_array[++iter] = ft_atoi(argv[count]);
		if (!input_array[iter] || input_array[iter] <= 0)
			(printf("Error: \nThe numbers must be > 0\n"), exit (-1));
	}
	return (input_array);
}
