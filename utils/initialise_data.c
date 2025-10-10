/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:18 by jromann           #+#    #+#             */
/*   Updated: 2025/10/06 13:00:46 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	valid_input(int argc, char **argv)
{
	int	i;
	int	k;

	k = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "PROGRAM REQUIRES 4 OR 5 ARGUMENTS\n", 34), 1);
	while (argv[++k])
	{
		i = -1;
		while (argv[k][++i])
			if (argv[k][i] < '0' || argv[k][i] > '9')
				return (write(2, "INVALID INPUT\n", 14), 1);
	}
	return (0);
}

static int	check_overflow(t_data *data)
{
	if (data->number_of_philosophers == -2 || data->time_to_die == -2
		|| data->time_to_eat == -2 || data->time_to_sleep == -2
		|| data->number_of_times_each_philosopher_must_eat == -2)
		return (write(2, "ARG OVERFLOW\n", 13), 1);
	return (0);
}
static int	initialise_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (protected_pthread_mutex_init(&data->forks[i], data, NULL) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	initialise_data(t_data *data, int argc, char **argv)
{
	if (valid_input(argc, argv) == 1)
		return (1);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (check_overflow(data) == 1)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (cleanup(NULL, data, FAILURE, "FORK FAILED\n"));
	data->status = EVERYONE_ALIVE;
	data->threads_ready = FALSE;
	data->start_time = 0;
	data->philos_done = 0;
	// initialise_queue(data);
	if (protected_pthread_mutex_init(&data->main_mutex, data, NULL) == 1)
		return (1);
	if (initialise_forks(data) == 1)
		return (1);
	return (0);
}
