/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/10/07 16:48:15 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void rotate(t_philosopher *philo)
{
	size_t iter;
	t_philosopher temp;

	iter = 0;
	temp = philo[0];
	while((int)iter < philo->data->number_of_philosophers - 1)
	{
		philo[iter] = philo[iter + 1];
		iter++;
	}
	philo[iter] = temp;
}

void	nextinline(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->main_mutex);
	if	(philo[0].ready == READY)
		return rotate(philo);
	philo[0].ready = READY;
	rotate(philo);
	pthread_mutex_unlock(&philo->data->main_mutex);
}

int	initialise_philos(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = malloc(sizeof(t_philosopher)
			* data->number_of_philosophers);
	if (!philo)
		return (cleanup(philo, philo->data, FAILURE, "MALLOC FAILED"));
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].life = 1;
		philo[i].left_fork = 0;
		philo[i].right_fork = 0;
		philo[i].data = data;
		philo[i].time_alive = 0;
		philo[i].eaten_meals = 0;
		philo[i].last_eaten[0] = 0;
		philo[i].ready = NOTREADY;
		protected_pthread_create(philo, philo->data, i);
		i++;
	}
	if(data->status == EVERYONE_ALIVE)
	{
		pthread_mutex_lock(&data->main_mutex);
		data->start_time = gettime(philo);
		data->threads_ready = TRUE;
		pthread_mutex_unlock(&data->main_mutex);
		while (data->status == EVERYONE_ALIVE)
			alive_check(philo);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philo[i].newthread, NULL);
		i++;
	}
	cleanup(philo, data, SUCCESS, NULL);
	return (0);
}
