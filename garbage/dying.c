/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:04:31 by jromann           #+#    #+#             */
/*   Updated: 2025/09/01 14:57:34 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void dying(t_container *container)
{
    usleep(container->data.time_to_eat);
    pthread_mutex_unlock(container->philo.mutex);
}