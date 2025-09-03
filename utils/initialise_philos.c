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

void	initialise_philos(t_container *container)
{
    int i;

    i = 0;
    while(i < container->data.number_of_philosophers)
    {
        container->philo[i].id = i + 1;
        container->philo[i].life = 1;
        container->philo[i].left_fork = 0;
        container->philo[i].right_fork = 0;
        pthread_create(&container->philo[i].newthread, NULL, routine, (void *)container);
        i++;
    }
    i = 0;
    while(i < container->data.number_of_philosophers)
    {
        pthread_join(container->philo[i].newthread, NULL);
        i++;
    }
}