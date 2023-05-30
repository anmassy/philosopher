/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:32:35 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/29 16:41:16 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 5 && ac != 6)
		return (0);
	ft_memset(&d, 0, sizeof(t_philo));
	if (!init_val(&d, av) || !check_arg(av))
		return (0);
	d.philo = malloc(sizeof(t_philo) * d.n_philo);
	if (!d.philo)
		return (0);
	if (!init_philo(&d))
		return (0);
	return (0);
}
