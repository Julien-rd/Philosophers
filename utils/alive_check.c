/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/09/13 16:21:51 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static int	philo_done(t_philosopher *philo)
// {
// 	if (philo->data->number_of_times_each_philosopher_must_eat == -1)
// 		return (0);
// 	if (philo->eaten_meals == philo->data->number_of_times_each_philosopher_must_eat)
// 	{
// 		philo->data->philos_done += 1;
// 		if (philo->data->philos_done == philo->data->number_of_times_each_philosopher_must_eat)
// 		{
// 			printaction("Dinner done", philo);
// 			exit(0);
// 		}
// 	}
// 	return (0);
// }

void	alive_check(t_philosopher *philo)
{
	int i;
	size_t time;

	time = gettime(philo);
	i = 0;
	protected_pthread_mutex_lock(&philo->data->main_mutex, philo);
	while (i < philo->data->number_of_philosophers)
	{
		if ((int)time - philo[i].last_eaten > philo->data->time_to_die)
		{
			// printaction("died", philo);
			printf("%zu %d died\n", gettime(philo), philo->id);
			philo->data->status = 0;
			protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
			exit(1);
		}
		i++;
	}
	protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
}