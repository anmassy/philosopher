/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:32:35 by anmassy           #+#    #+#             */
/*   Updated: 2023/09/13 12:08:10 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	writen(t_philo *philo, char *msg)
{
	long int	time;

	pthread_mutex_lock(&philo->arg->writing);
	time = timer() - philo->arg->t_start;
	if (!philo->arg->value && time && !condition(philo, 0))
		printf("%ld %d %s\n", time, philo->pos, msg);
	pthread_mutex_unlock(&philo->arg->writing);
}

void	ft_destroy(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->n_philo)
	{
		pthread_mutex_destroy(&d->philo[i].lfork);
		pthread_mutex_destroy(d->philo[i].rfork);
		i++;
	}
	free(d->philo);
	pthread_mutex_destroy(&d->writing);
	pthread_mutex_destroy(&d->m_eat);
	pthread_mutex_destroy(&d->m_stop);
	pthread_mutex_destroy(&d->dead);
}

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
	ft_destroy(&d);
	return (0);
}
