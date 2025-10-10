/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:08:10 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	alive_check(t_philosopher *philo)
{
	size_t	iter;
	size_t	time;

	iter = 0;
	pthread_mutex_lock(&philo->data->main_mutex);
	if (philo->data->philos_done == philo->data->philo_amount)
	{
		philo->data->status = 0;
		if (write(1, "dinner done!\n", 13) == -1)
			return (pthread_mutex_unlock(&philo->data->main_mutex), 1);
		philo->data->status = 0;
		pthread_mutex_unlock(&philo->data->main_mutex);
		return (0);
	}
	while (iter < philo->data->philo_amount)
	{
		time = gettime(philo);
		if (time - philo[iter].last_eaten > philo->data->time_to_die)
		{
			print_num(gettime(&philo[iter]));
			if (write(1, " ", 1) == -1)
				return (pthread_mutex_unlock(&philo->data->main_mutex), 1);
			print_num(philo[iter].id);
			if (write(1, " died\n", 6) == -1)
				return (pthread_mutex_unlock(&philo->data->main_mutex), 1);
			philo->data->status = 0;
			pthread_mutex_unlock(&philo->data->main_mutex);
			return (0);
		}
		iter++;
	}
	pthread_mutex_unlock(&philo->data->main_mutex);
	return (0);
}
