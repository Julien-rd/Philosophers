/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 12:22:00 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	initialise_philos(t_data *data, t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	philo = malloc(sizeof(t_philosopher) * data->philos_total);
	if (!philo)
		return (cleanup(philo, philo->data, FAILURE, "MALLOC FAILED"));
	while (iter < data->philos_total)
	{
		philo[iter].id = iter + 1;
		philo[iter].life = 1;
		philo[iter].left_fork = 0;
		philo[iter].right_fork = 0;
		philo[iter].data = data;
		philo[iter].time_alive = 0;
		philo[iter].eaten_meals = 0;
		philo[iter].last_eaten = 0;
		philo[iter].ready = NOTREADY;
		if (protected_pthread_create(philo, philo->data, iter) == 1)
			return (data->status = !EVERYONE_ALIVE,
				philo->data->threads_ready = TRUE, 0);
		iter++;
	}
	return (0);
}

static void	monitor_philos(t_philosopher *philo)
{
	if (philo->data->status == EVERYONE_ALIVE)
	{
		pthread_mutex_lock(&philo->data->main_mutex);
		philo->data->start_time = gettime(philo);
		philo->data->threads_ready = TRUE;
		pthread_mutex_unlock(&philo->data->main_mutex);
		while (philo->data->status == EVERYONE_ALIVE)
			alive_check(philo);
	}
}

static void	join_threads(t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	while (iter < philo->data->philos_total)
	{
		pthread_join(philo[iter].newthread, NULL);
		iter++;
	}
}

int	start_simulation(t_data *data)
{
	t_philosopher	philo;

	if (initialise_philos(data, &philo) == 1)
		return (1);
	monitor_philos(&philo);
	join_threads(&philo);
	cleanup(&philo, data, SUCCESS, NULL);
	return (0);
}
