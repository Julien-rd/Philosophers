/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:54:21 by jromann           #+#    #+#             */
/*   Updated: 2025/09/01 14:01:47 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eating(t_container *container)
{
    pthread_mutex_lock(container->philo.mutex);
    usleep(container->data.time_to_eat);
    pthread_mutex_unlock(container->philo.mutex);
}