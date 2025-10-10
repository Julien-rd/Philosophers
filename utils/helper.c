/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:27:48 by jromann           #+#    #+#             */
/*   Updated: 2025/10/06 13:44:11 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_num(int n)
{
	char	buf[12];
	int		i;
	int		is_negative;

	i = 11;
	buf[i--] = '\0';
	if (n == 0)
	{
		buf[i] = '0';
		write(1, &buf[i], 1);
		return ;
	}
	is_negative = (n < 0);
	if (is_negative == 1)
		n = -n;
	while (n > 0)
	{
		buf[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (is_negative)
		buf[i--] = '-';
	write(1, &buf[i + 1], 11 - i - 1);
}

size_t	ft_strlen(char *str)
{
	size_t	iter;

	iter = 0;
	while (str[iter])
		iter++;
	return (iter);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	if (result > 2147483647)
		return (-2);
	return (result * sign);
}