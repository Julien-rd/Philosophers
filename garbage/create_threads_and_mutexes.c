/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads_and_mutexes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:05:31 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 10:47:25 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	initialise_philosophers(t_container *container, int i)
// {
// 	container->philo[i].id = i + 1;
// 	container->philo[i].right_fork = 1;
// 	container->philo[i].left_fork = 0;
// 	container->philo[i].life = 1;
// 	pthread_mutex_init(&container->philo[i].mutex, NULL);
// }

// void	create_threads_and_mutexes(t_container *container)
// {
// 	int i;

// 	i = 0;
// 	container->philo = malloc(sizeof(t_philosopher)
// 			* (container->data.number_of_philosophers + 1));
// 	if (!container->philo)
// 		exit(1);
// 	while (i < container->data.number_of_philosophers)
// 	{
// 		container->philo[i].id = i + 1;
// 		container->philo[i].right_fork = 1;
// 		container->philo[i].left_fork = 0;
// 		container->philo[i].life = 1;
//         pthread_mutex_init(&container->philo[i].mutex, NULL);
// 		// pthread_create(&container->philo[i].newthread, NULL, NULL, container);
// 		i++;
// 	}
// }