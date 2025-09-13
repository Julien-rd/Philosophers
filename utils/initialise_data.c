/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:18 by jromann           #+#    #+#             */
/*   Updated: 2025/09/13 13:50:19 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	valid_input(int argc, char **argv)
{
	int	i;
	int	k;

	k = 0;
	if (argc < 5 || argc > 6)
	{
		printf("program requires 4 or 5 arguments");
		return (1);
	}
	while (argv[++k])
	{
		i = -1;
		while (argv[k][++i])
			if (argv[k][i] < '0' || argv[k][i] > '9')
			{
				printf("invalid input\n");
				return (0);
			}
	}
	return (1);
}

static int	check_overflow(t_data *data)
{
	if (data->number_of_philosophers == -2 || data->time_to_die == -2
		|| data->time_to_eat == -2 || data->time_to_sleep == -2
		|| data->number_of_times_each_philosopher_must_eat == -2)
	{
		printf("arg > int_max");
		// cleanup() TODO
		return (1);
	}
	return (0);
}
static int	initialise_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (protected_pthread_mutex_init(&data->forks[i], NULL) == 1)
			return (1); // FREE MUTEX_INIT
		i++;
	}
	return (0);
}

static int initialise_queue(t_data *data)
{
	int i;
	
	i = -1;
	data->queue = (int *)protected_malloc(sizeof(int) * data->number_of_philosophers);
	while(++i < data->number_of_philosophers)
		data->queue[i] = i + 1;
	return 0;
}
int	initialise_data(t_data *data, int argc, char **argv)
{
	if (!valid_input(argc, argv))
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
	data->forks = (pthread_mutex_t *)protected_malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (1);
	data->status = EVERYONE_ALIVE;
	data->threads_ready = FALSE;
	if (protected_pthread_mutex_init(&data->main_mutex, NULL) == 1)
		return (1);
	if (protected_pthread_mutex_init(&data->death_mutex, NULL) == 1)
		return (1);
	data->start_time = 0;
	data->philos_done = 0;
	initialise_queue(data);
	if (initialise_forks(data) == 1)
		return (1);
	return (0);
}
