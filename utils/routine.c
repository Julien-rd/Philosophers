/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:39:56 by jromann           #+#    #+#             */
/*   Updated: 2025/10/06 13:00:39 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void wait_for_threads(t_philosopher *philo)
{
	while(philo->data->threads_ready == FALSE)
		;
}

void	*routine(void *ptr)
{
	t_philosopher *philo;

	philo = (t_philosopher *)ptr;
    wait_for_threads(philo);
	while (philo->data->status == EVERYONE_ALIVE)
	{
		eat(philo);
		if (philo->data->status == !EVERYONE_ALIVE)
			break ;
		nap(philo);
		if (philo->data->status == !EVERYONE_ALIVE)
			break ;
		think(philo);
	}
	return NULL;
}