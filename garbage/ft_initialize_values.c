/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:06:44 by jromann           #+#    #+#             */
/*   Updated: 2025/08/25 11:59:57 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_initialize_values(int argc, char **argv, t_philosopher **philo)
{
	int	i;

    i = 0;
	philo[i] = malloc(sizeof(t_philosopher));
	if (!philo[i])
		ft_free_and_exit(philo);
	philo[i]->id = i + 1;
	philo[i]->amount = ft_atoi(argv[1]);
	philo[i]->die_t = ft_atoi(argv[2]);
	philo[i]->eat_t = ft_atoi(argv[3]);
	philo[i]->sleep_t = ft_atoi(argv[4]);
	if (argc == 6)
		philo[i]->max_eat = ft_atoi(argv[5]);
	else
		philo[i]->max_eat = -1;
	while (++i < philo[0]->amount)
	{
		philo[i] = malloc(sizeof(t_philosopher));
		if (!philo[i])
			ft_free_and_exit(philo);
		philo[i]->id = i + 1;
		philo[i]->amount = philo[0]->amount;
		philo[i]->die_t = philo[0]->die_t;
		philo[i]->eat_t = philo[0]->eat_t;
		philo[i]->sleep_t = philo[0]->sleep_t;
		philo[i]->max_eat = philo[0]->max_eat;
	}
}
