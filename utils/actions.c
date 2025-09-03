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

void	optimised_usleep(size_t time, t_container *container)
{
	size_t	end;
    size_t remaining;

    remaining = 1;
	time *= 1000;
    end = gettime(container) + time;
    while(remaining > 0)
    {
        remaining = end - gettime(container);
        if (remaining > 1000)
            usleep(remaining / 2);
    }
    
}

void	eat(t_container *container)
{
	printf("%zu %d is eating\n", gettime(container), container->philo->id);
	optimised_usleep(container->data.time_to_eat, container);
}

void	nap(t_container *container)
{
	printf("%zu %d is sleeping\n", gettime(container), container->philo->id);
	optimised_usleep(container->data.time_to_sleep, container);
}

void	think(t_container *container)
{
	printf("%zu %d is thinking\n", gettime(container), container->philo->id);
}