/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:34:08 by jromann           #+#    #+#             */
/*   Updated: 2025/10/10 15:35:17 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pickup_fork(t_philosopher *philo, int flag)
{
	if (flag == LEFT_FORK)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		printaction(" has taken a fork\n", philo);
		philo->left_fork = 1;
		if (ready2eat(philo))
			return ;
		else
			pickup_fork(philo, RIGHT_FORK);
	}
	if (flag == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->philo_amount]);
		printaction(" has taken a fork\n", philo);
		philo->right_fork = 1;
		if (ready2eat(philo))
			return ;
		else
			pickup_fork(philo, LEFT_FORK);
	}
}
