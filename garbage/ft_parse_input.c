/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:07:45 by jromann           #+#    #+#             */
/*   Updated: 2025/09/01 11:24:34 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	**ft_parse_input(int argc, char **argv)
{
	t_philosopher	**philo;
	int				i;

	i = 0;
	ft_valid_input(argc, argv);
	philo = malloc(sizeof(t_philosopher *) * argc);
	if (!philo)
		exit(1);
	ft_initialize_values(argc, argv, philo);
	return (philo);
}