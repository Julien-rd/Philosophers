/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:45:41 by jromann           #+#    #+#             */
/*   Updated: 2025/10/11 09:50:21 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printaction(char *str, t_philosopher *philo)
{
	if (philo->data->status == 0 || philo->data->function_fail == true)
		return ;
	pthread_mutex_lock(&philo->data->main_mutex);
	if (philo->data->status == ACTIVE)
	{
		print_num(gettime(philo), philo->data);
		if (write(1, " ", 1) == -1)
		{
			philo->data->function_fail = true;
			pthread_mutex_unlock(&philo->data->main_mutex);
			return ;
		}
		print_num(philo->id, philo->data);
		if (write(1, str, ft_strlen(str)) == -1)
		{
			philo->data->function_fail = true;
			pthread_mutex_unlock(&philo->data->main_mutex);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->data->main_mutex);
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
	pthread_mutex_lock(&philo->data->main_mutex);
	if (philo->eaten_meals == philo->data->required_meals)
		philo->data->philos_done += 1;
	pthread_mutex_unlock(&philo->data->main_mutex);
	philo->right_fork = 0;
	philo->left_fork = 0;
	philo->time_alive = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->philo_amount]);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	usleep(0);
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
	usleep(0);
}
