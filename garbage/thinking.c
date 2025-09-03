/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:01:49 by jromann           #+#    #+#             */
/*   Updated: 2025/09/01 14:02:04 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void thinking(t_container *container)
{
    usleep(container->data.time_to_eat);
    pthread_mutex_unlock(container->philo.mutex);
}