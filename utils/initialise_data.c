/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:18 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 13:57:06 by jromann          ###   ########.fr       */
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

static int	initialise_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_amount);
	if (!data->forks)
		return (cleanup(NULL, data, FAILURE, "FORK FAILED\n"));
	while (i < data->philo_amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	initialise_args(t_data *data, int argc, char **argv)
{
	bool	overflow;

	overflow = false;
	data->philo_amount = ft_atoi(argv[1], &overflow);
	data->time_to_die = ft_atoi(argv[2], &overflow);
	data->time_to_eat = ft_atoi(argv[3], &overflow);
	data->time_to_sleep = ft_atoi(argv[4], &overflow);
	if (argc == 6)
		data->required_meals = ft_atoi(argv[5], &overflow);
	else
		data->required_meals = -1;
	if (overflow == true)
		return (write(2, "OVERFLOW\n", 9), 1);
	data->status = EVERYONE_ALIVE;
	data->threads_ready = FALSE;
	data->start_time = 0;
	data->philos_done = 0;
	return (0);
}

int	initialise_data(t_data *data, int argc, char **argv)
{
	if (valid_input(argc, argv) == 1)
		return (1);
	if (initialise_args(data, argc, argv) == 1)
		return (1);
	if (pthread_mutex_init(&data->main_mutex, NULL) != 0)
		return (write(2, "PTHREAD_MUTEX_INIT FAILED\n", 26), 1);
	if (initialise_forks(data) == 1)
		return (1);
	return (0);
}
