/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:00:31 by jromann           #+#    #+#             */
/*   Updated: 2025/09/01 14:01:03 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void sleeping(t_container *container)
{
    // pthread_mutex_lock(container->philo.mutex);
    usleep(container->data.time_to_sleep);
    // pthread_mutex_unlock(container->philo.mutex);
}