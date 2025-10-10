/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 12:23:19 by jromann          ###   ########.fr       */
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

static int	everybody_done(t_philosopher *philo)
{
	if (philo->data->philos_done == philo->data->philos_total)
	{
		philo->data->status = 0;
		write(1, "dinner done!\n", 13);
		philo->data->status = 0;
		return (1);
	}
	return (0);
}
static int	someone_died(t_philosopher *philo)
{
	size_t	iter;
	size_t	time;

	iter = 0;
	while (iter < philo->data->philos_total)
	{
		time = gettime(philo);
		if (time - philo[iter].last_eaten > philo->data->time_to_die)
		{
			printf("%zu\n", iter);
			printf("id: %zu\n", philo[iter].id);
			print_num(gettime(&philo[iter]));
			write(1, " ", 1);
			print_num(philo[iter].id);
			write(1, " died\n", 6);
			philo->data->status = 0;
			return (1);
		}
		iter++;
	}
	return (0);
}

void	alive_check(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->main_mutex);
	if (everybody_done(philo))
		return ((void)pthread_mutex_unlock(&philo->data->main_mutex));
	if (someone_died(philo))
		return ((void)pthread_mutex_unlock(&philo->data->main_mutex));
	pthread_mutex_unlock(&philo->data->main_mutex);
}
