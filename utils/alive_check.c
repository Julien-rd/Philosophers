/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 10:29:35 by jromann          ###   ########.fr       */
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
	int		i;
	size_t	time;

	i = 0;
	pthread_mutex_lock(&philo->data->main_mutex);
	if (philo->data->philos_done == philo->data->number_of_philosophers)
	{
		philo->data->status = 0;
		write(1, "dinner done!\n", 13);
		philo->data->status = 0;
		pthread_mutex_unlock(&philo->data->main_mutex);
		return ;
	}
	while (i < philo->data->number_of_philosophers)
	{
		time = gettime(philo);
		if ((int)time - philo[i].last_eaten[0] > philo->data->time_to_die)
		{
			print_num(gettime(&philo[i]));
			write(1, " ", 1);
			print_num(philo[i].id);
			write(1, " died\n", 6);
			philo->data->status = 0;
			pthread_mutex_unlock(&philo->data->main_mutex);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->main_mutex);
}
