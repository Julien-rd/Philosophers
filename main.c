/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:24:18 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 13:00:28 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_container container;

	initialise_data(&container, argc, argv);
	initialise_philos(&container);
	return (0);
}