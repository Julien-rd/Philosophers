/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:16:54 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 13:07:13 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialise_philos(t_data *data)
{
    int i;
    t_philosopher *philo;
    i = 0;

    philo = protected_malloc(sizeof(t_philosopher) * data->number_of_philosophers);
    while(i < data->number_of_philosophers)
    {
        philo[i].id = i + 1;
        philo[i].life = 1;
        philo[i].left_fork = 0;
        philo[i].right_fork = 0;
        philo[i].data = data;
        protected_pthread_create(philo, i);
        i++;
    }
    protected_pthread_mutex_lock(data->main_mutex, NULL);
    data->threads_ready = TRUE;
    data->start_time = gettime(philo);
    protected_pthread_mutex_unlock(data->main_mutex, NULL);
    i = 0;
    while(i < data->number_of_philosophers)
    {
        protected_pthread_join(philo, i);
        i++;
    }
}
