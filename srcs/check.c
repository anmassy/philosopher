/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:45 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/09 15:00:39 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_overflow(char *arg)
{
	int	temp;

	temp = ft_atoi(arg);
	if ((temp >= -2147483648 || temp <= 2147483647) && ft_strlen(arg) < 12)
		return (1);
	return (0);
}

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!check_overflow(av[i]))
			return (0);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
