/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:45:41 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:45:53 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	printaction(char *str, t_philosopher *philo)
{
	if (philo->data->status == 0)
		return (0);
	pthread_mutex_lock(&philo->data->main_mutex);
	if (philo->data->status == ACTIVE)
	{
		print_num(gettime(philo));
		if (write(1, " ", 1) == -1)
			return (philo->data->function_fail = true,
				pthread_mutex_unlock(&philo->data->main_mutex), 1);
		print_num(philo->id);
		if (write(1, str, ft_strlen(str)) == -1)
			return (philo->data->function_fail = true,
				pthread_mutex_unlock(&philo->data->main_mutex), 1);
	}
	pthread_mutex_unlock(&philo->data->main_mutex);
	return (pthread_mutex_unlock(&philo->data->main_mutex), 0);
}

void	optimised_usleep(size_t time, t_philosopher *philo)
{
	size_t	end;
	int		remaining;

	if (time == 0)
		return ;
	remaining = 1;
	end = gettime(philo) + time;
	while (remaining > 0)
	{
		remaining = end - gettime(philo);
		if (remaining > 1000 && usleep((remaining * 1000) / 2) == -1)
		{
			philo->data->function_fail = true;
			return ;
		}
	}
}
int	ready2eat(t_philosopher *philo)
{
	if (philo->right_fork == 1 && philo->left_fork == 1)
		return (1);
	return (0);
}

void	eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		pickup_fork(philo, RIGHT_FORK);
	else
		pickup_fork(philo, LEFT_FORK);
	printaction(" is eating\n", philo);
	philo->last_eaten = gettime(philo);
	if (philo->data->status == 0)
		return ;
	optimised_usleep(philo->data->time_to_eat, philo);
	philo->eaten_meals += 1;
	if (philo->eaten_meals == philo->data->required_meals)
		philo->data->philos_done += 1;
	philo->right_fork = 0;
	philo->left_fork = 0;
	philo->time_alive = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->philo_amount]);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	philo->ready = NOTREADY;
}

void	nap(t_philosopher *philo)
{
	printaction(" is sleeping\n", philo);
	if (philo->data->status == 0)
		return ;
	optimised_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philosopher *philo)
{
	printaction(" is thinking\n", philo);
}
