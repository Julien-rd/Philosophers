/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:39:56 by jromann           #+#    #+#             */
/*   Updated: 2025/09/03 13:05:53 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{
	t_container *container;

	container = (t_container *)ptr;
    // return NULL;
	while (container->data.status == EVERYONE_ALIVE)
	{
		eat(container);
		nap(container);
		think(container);
	}
	return NULL;
}