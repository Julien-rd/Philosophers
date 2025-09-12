/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/09/12 16:40:10 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		protected_pthread_create(philo, i);
		i++;
	}
	protected_pthread_mutex_lock(&data->main_mutex, NULL);
	data->start_time = gettime(philo);
	data->threads_ready = TRUE;
	protected_pthread_mutex_unlock(&data->main_mutex, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		protected_pthread_join(philo, i);
		i++;
	}
	return (0);
}
