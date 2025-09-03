/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:18 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 12:55:33 by jromann          ###   ########.fr       */
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
		exit(1);
	}
	while (argv[++k])
	{
		i = -1;
		while (argv[k][++i])
			if (argv[k][i] < '0' || argv[k][i] > '9')
			{
				printf("invalid input\n");
				exit(1);
			}
	}
	return (1);
}

static void	check_overflow(t_data *data)
{
	if (data->number_of_philosophers == -2 || data->time_to_die == -2
		|| data->time_to_eat == -2 || data->time_to_sleep == -2
		|| data->number_of_times_each_philosopher_must_eat == -2)
	{
		printf("arg > int_max");
		exit(1);
	}
}
static void	initialise_forks(t_container *container)
{
	int	i;

	i = 0;
	while (i < container->data.number_of_philosophers)
	{
		pthread_mutex_init(&container->data.forks[i], NULL);
		i++;
	}
}
void	initialise_data(t_container *container, int argc, char **argv)
{
	t_philosopher	philo[200];
	pthread_mutex_t	forks[200];

	valid_input(argc, argv);
	container->philo = philo;
	container->data.forks = forks;
	container->data.number_of_philosophers = ft_atoi(argv[1]);
	container->data.time_to_die = ft_atoi(argv[2]);
	container->data.time_to_eat = ft_atoi(argv[3]);
	container->data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		container->data.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		container->data.number_of_times_each_philosopher_must_eat = -1;
	check_overflow(&container->data);
	container->data.status = EVERYONE_ALIVE;
	container->data.start_time = 0;
	container->data.start_time = gettime(container);
	initialise_forks(container);
}
