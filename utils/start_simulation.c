/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/10/14 13:04:39 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialise_philos(t_data *data, t_philosopher **philo)
{
	size_t	iter;

	iter = 0;
	*philo = malloc(sizeof(t_philosopher) * data->philo_amount);
	if (!*philo)
		return ;
	while (iter < data->philo_amount)
	{
		(*philo)[iter].id = iter + 1;
		(*philo)[iter].left_fork = 0;
		(*philo)[iter].right_fork = 0;
		(*philo)[iter].data = data;
		(*philo)[iter].time_alive = 0;
		(*philo)[iter].eaten_meals = 0;
		(*philo)[iter].last_eaten = 0;
		(*philo)[iter].ready = NOTREADY;
		if (protected_pthread_create(*philo, iter) == 1)
			break ;
		iter++;
	}
	data->open_threads = iter;
}

static int	monitoring_philos(t_data *data, t_philosopher **philo)
{
	if (data->status == ACTIVE)
	{
		pthread_mutex_lock(&data->main_mutex);
		data->start_time = gettime(*philo);
		data->threads_ready = true;
		pthread_mutex_unlock(&data->main_mutex);
		if (data->open_threads != data->philo_amount)
			data->status = INACTIVE;
		while (data->status == ACTIVE)
		{
			if (status_check(*philo) == 1)
				return (data->status = INACTIVE, 1);
		}
	}
	return (0);
}

static void	join_philos(t_data *data, t_philosopher **philo)
{
	size_t	iter;

	iter = 0;
	while (iter < data->open_threads)
	{
		pthread_join((*philo)[iter].newthread, NULL);
		iter++;
	}
}

static int	one_philo(t_data *data)
{
	t_philosopher	philo;

	philo.data = data;
	if (data->philo_amount > 1)
		return (0);
	data->start_time = gettime(&philo);
	print_num(gettime(&philo), data);
	pthread_mutex_lock(&data->forks[0]);
	if (safe_write(1, " 1 has picked up a fork\n", 24, data) == -1)
		return (1);
	optimised_usleep(data->time_to_die, &philo);
	print_num(gettime(&philo), data);
	pthread_mutex_unlock(&data->forks[0]);
	if (safe_write(1, " 1 has died\n", 12, data) == -1)
		return (1);
	return (1);
}

int	start_simulation(t_data *data)
{
	t_philosopher	*philo;

	if (one_philo(data))
		return (cleanup(NULL, data, SUCCESS, NULL));
	initialise_philos(data, &philo);
	if (philo == NULL)
		return (cleanup(philo, data, FAILURE, NULL));
	monitoring_philos(data, &philo);
	join_philos(data, &philo);
	return (cleanup(philo, data, SUCCESS, NULL));
}
