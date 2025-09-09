/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:43:41 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 12:51:24 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	gettime(t_philosopher *philo)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * 1000 + tv.tv_sec / 1000) - philo->data->start_time);
	//cleanup(); TODO
	exit(1);
}