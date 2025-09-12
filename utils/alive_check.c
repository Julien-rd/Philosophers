/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/09/12 16:43:07 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int philo_done(t_philosopher *philo)
{
	if (philo->data->number_of_times_each_philosopher_must_eat == -1)
		return 0;
	if (philo->eaten_meals == philo->data->number_of_times_each_philosopher_must_eat)
	{
		philo->data->philos_done += 1;
		if (philo->data->philos_done == philo->data->number_of_times_each_philosopher_must_eat)
		{
			printaction("Dinner done", philo);
			exit(0);
		}
	}
	return 0;
}
void	alive_check(t_philosopher *philo, int action)
{
	int time_needed;
	size_t time;

	time = 0;
	protected_pthread_mutex_lock(&philo->data->main_mutex, philo);
	time_needed = philo->last_eaten + action;
	if (philo_done(philo))
		time = 0;//TODO philo thread gets closed
	if ((size_t)time_needed >= gettime(philo) + (size_t)philo->data->time_to_die || philo->data->number_of_philosophers == 1)
	{
		protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
		protected_pthread_mutex_lock(&philo->data->death_mutex, philo);
		if((size_t)(philo->last_eaten + philo->data->time_to_die) > gettime(philo))
			time = (size_t)(philo->last_eaten + philo->data->time_to_die) - gettime(philo);
		optimised_usleep(time, philo);
		printaction("died", philo);
		exit(1);
	}
	else
		protected_pthread_mutex_unlock(&philo->data->main_mutex, philo);
}