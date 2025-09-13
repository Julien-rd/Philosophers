/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/09/13 15:59:00 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	change_prio(t_philosopher *philo, int pos, int id)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philosophers)
	{
		if (pos == i)
		{
			while (i + 1 < philo->data->number_of_philosophers)
			{
				philo->data->queue[i] = philo->data->queue[i + 1];
				i++;
			}
			philo->data->queue[i] = id;
			return ;
		}
		i++;
	}
}

static int	forks_available(t_philosopher *philo, int id)
{
	int	left_neighbor;
	int	right_neighbor;

	left_neighbor = ((id - 2 + philo->data->number_of_philosophers)
			% philo->data->number_of_philosophers);
	right_neighbor = (id % philo->data->number_of_philosophers);
	if (philo[right_neighbor].left_fork != 1
		&& philo[left_neighbor].right_fork != 1)
	{
		philo[id - 1].right_fork = 1;
		philo[id - 1].left_fork = 1;
		philo[id - 1].ready = 1;
		return (1);
	}
	return (0);
}
void	nextinline(t_philosopher *philo)
{
	int	i;
	int z;
	int	id;
	int changes;

	i = 0;
	changes = 0;
	protected_pthread_mutex_lock(&philo->data->main_mutex, philo);
	while (i < philo->data->number_of_philosophers - changes)
	{
		id = philo->data->queue[i];
		z = 0;
		if (forks_available(philo, id))
		{
			while(philo[z].id != id)
				z++;
			philo[z].ready = READY;
			change_prio(philo, i, id);
			changes++;
		}
		i++;
	}
	protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
}

int	initialise_philos(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = protected_malloc(sizeof(t_philosopher)
			* data->number_of_philosophers);
	if (!philo)
		return (cleanup(philo, FAILURE, "MALLOC FAILED"));
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].life = 1;
		philo[i].left_fork = 0;
		philo[i].right_fork = 0;
		philo[i].data = data;
		philo[i].time_alive = 0;
		philo[i].eaten_meals = 0;
		philo[i].last_eaten = 0;
		philo[i].ready = NOTREADY;
		protected_pthread_create(philo, i);
		i++;
	}
	protected_pthread_mutex_lock(&data->main_mutex, NULL);
	data->start_time = gettime(philo);
	data->threads_ready = TRUE;
	protected_pthread_mutex_unlock(&data->main_mutex, NULL);
	while (data->status == EVERYONE_ALIVE)
	{
		nextinline(philo);
		alive_check(philo);
		// optimised_usleep(8, philo);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		protected_pthread_join(philo, i);
		i++;
	}
	return (0);
}
