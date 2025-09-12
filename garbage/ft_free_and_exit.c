/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:21:37 by jromann           #+#    #+#             */
/*   Updated: 2025/09/12 10:56:52 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_and_exit(t_philosopher **philo)
{
	int	i;

    i = 0;
    while(philo[i])
    {
        free(philo[i]);
        i++;
    }
    free(philo);
//     exit(1);
}