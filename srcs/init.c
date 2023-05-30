/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:10 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/30 17:31:58 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_data *d)
{
	if (pthread_mutex_init(&d->writing, NULL) != 0)
		return (0);
	return (1);
}

int	init_val(t_data *d, char **av)
{
	if (!init_mutex(d))
		return (0);
	d->n_philo = ft_atoi(av[1]);
	d->t_die = ft_atoi(av[2]);
	d->t_eat = ft_atoi(av[3]);
	d->t_sleep = ft_atoi(av[4]);
	if (av[5])
		d->n_eat = ft_atoi(av[5]);
	if (d->n_philo < 1 || d->t_die < 0 || d->t_eat < 0 || d->t_sleep < 0)
		return (0);
	return (1);
}

int	init_philo(t_data *d)
{
	int	i;

	d->t_start = timer();
	i = 0;
	while (i < d->n_philo)
	{
		d->philo[i].pos = i + 1;
		d->philo[i].count = 0;
		d->philo[i].last_eat = 0;
		d->philo[i].stop = 0;
		d->philo[i].arg = d;
		d->philo[i].rfork = NULL;
		if (pthread_mutex_init(&(d->philo[i].lfork), NULL) != 0)
			return (0);
		if (d->n_philo - 1 == i)
			d->philo[i].rfork = &(d->philo[0].lfork);
		else
			d->philo[i].rfork = &(d->philo[i + 1].lfork);
		if (pthread_create(&d->philo[i].thread, NULL, &routine, &(d->philo[i])) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < d->n_philo)
	{
		if (pthread_join(d->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
