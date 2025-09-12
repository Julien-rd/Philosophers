/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:24:18 by jromann           #+#    #+#             */
/*   Updated: 2025/09/12 13:39:36 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (initialise_data(&data, argc, argv) == 1)
		return (1);
	if (initialise_philos(&data) == 1)
		return (1);
	// cleanup(, SUCCESS, NULL);
	return (0);
}