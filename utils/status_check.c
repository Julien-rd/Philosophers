/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:36:17 by jromann           #+#    #+#             */
/*   Updated: 2025/10/11 09:51:30 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	safe_write(int fd, char *str, int size, t_data *data)
{
	if (data->function_fail == true)
		return (-1);
	if (write(fd, str, size) == -1)
	{
		data->function_fail = true;
		return (-1);
	}
	return (0);
}

static void	alive_check(t_philosopher *philo)
{
	size_t	iter;
	size_t	time;

	iter = 0;
	while (iter < philo->data->philo_amount)
	{
		time = gettime(philo);
		if (time - philo[iter].last_eaten > philo->data->time_to_die)
		{
			print_num(gettime(&philo[iter]), philo->data);
			if (safe_write(1, " ", 1, philo->data) == -1)
				return ;
			print_num(philo[iter].id, philo->data);
			if (safe_write(1, " died\n", 6, philo->data) == -1)
				return ;
			philo->data->status = 0;
			return ;
		}
		iter++;
	}
}

int	dinner_done(t_philosopher *philo)
{
	if (philo->data->philos_done == philo->data->philo_amount)
	{
		philo->data->status = 0;
		print_num(gettime(philo), philo->data);
		if (write(1, "dinner done!\n", 13) == -1)
			return (1);
		philo->data->status = 0;
		return (1);
	}
	return (0);
}

int	status_check(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->main_mutex);
	if (!dinner_done(philo))
		alive_check(philo);
	pthread_mutex_unlock(&philo->data->main_mutex);
	return (0);
}
