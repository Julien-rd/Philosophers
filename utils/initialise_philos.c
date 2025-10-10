/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:33:32 by jromann          ###   ########.fr       */
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
		(*philo)[iter].life = 1;
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
			data->status = !ACTIVE;
		while (data->status == ACTIVE)
			if (alive_check(*philo) == 1)
				return (data->status = !ACTIVE, 1);
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

int	start_simulation(t_data *data)
{
	t_philosopher	*philo;

	initialise_philos(data, &philo);
	if (philo == NULL)
		return (cleanup(philo, data, FAILURE, NULL));
	monitoring_philos(data, &philo);
	join_philos(data, &philo);
	return (cleanup(philo, data, SUCCESS, NULL));
}
