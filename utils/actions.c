/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:45:41 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 14:44:06 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	optimised_usleep(size_t time, t_philosopher *philo)
{
	size_t	end;
    size_t remaining;

    remaining = 1;
    end = gettime(philo) + time;
    while(remaining > 0)
    {
        remaining = end - gettime(philo);
        if (remaining > 1000)
            usleep(remaining / 2);
    }
    
}
int ready2eat(t_philosopher *philo)
{
    if (philo->right_fork == 1 && philo->left_fork == 1)
        return 1;
    return 0;
}

void	eat(t_philosopher *philo)
{
	printf("%zu %d is eating\n", gettime(philo), philo->id);
    protected_pthread_mutex_unlock(philo->data->forks[philo->id % philo->data->number_of_philosophers], NULL);
    protected_pthread_mutex_unlock(philo->data->forks[philo->id % philo->data->number_of_philosophers - 1], NULL);
    philo->right_fork = 0;
    philo->left_fork = 0;
	optimised_usleep(philo->data->time_to_eat, philo);
}

void	nap(t_philosopher *philo)
{
	printf("%zu %d is sleeping\n", gettime(philo), philo->id);
	optimised_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philosopher *philo)
{
	printf("%zu %d is thinking\n", gettime(philo), philo->id);
}