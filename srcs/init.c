/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:10 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/09 16:45:28 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_data *d)
{
	if (pthread_mutex_init(&d->writing, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&d->m_eat, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&d->m_stop, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&d->dead, NULL) != 0)
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
	{
		d->n_eat = ft_atoi(av[5]);
		if (d->n_eat < 1)
			return (0);
	}
	else
		d->n_eat = -1;
	if (d->n_philo < 1 || d->t_die < 1 || d->t_eat < 1 || d->t_sleep < 1)
		return (0);
	return (1);
}

int	init_philo(t_data *d)
{
	int	i;

	d->t_start = timer();
	d->exit_val = 0;
	d->stop = 0;
	i = 0;
	while (i < d->n_philo)
	{
		d->philo[i].pos = i + 1;
		d->philo[i].count_eat = 0;
		d->philo[i].last_eat = timer();
		d->philo[i].arg = d;
		d->philo[i].rfork = NULL;
		if (pthread_mutex_init(&(d->philo[i].lfork), NULL) != 0)
			return (0);
		if (d->n_philo - 1 == i)
			d->philo[i].rfork = &(d->philo[0].lfork);
		else
			d->philo[i].rfork = &(d->philo[i + 1].lfork);
		i++;
	}
	return (1);
}

int	create_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->n_philo)
	{
		if (pthread_create(&d->philo[i].thread, \
			NULL, start_dinner, &(d->philo[i])))
			return (0);
		i++;
	}
	return (1);
}

void	*start_dinner(void *ph)
{
	t_philo		*philo;

	philo = (t_philo *)ph;
	if (philo->pos % 2 == 0)
		ft_usleep(philo->arg->t_eat / 10, philo);
	while (!condition(philo, 0))
	{
		routine(philo);
		if (++philo->count_eat == philo->arg->n_eat)
		{
			pthread_mutex_lock(&philo->arg->m_stop);
			if (philo->arg->n_philo != 1 && philo->arg->exit_val == 0
				&& ++philo->arg->stop == philo->arg->n_philo)
			{
				printf("Everyone eating %d time(s) !\n", philo->arg->n_eat);
				condition(philo, 2);
			}
			pthread_mutex_unlock(&philo->arg->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}
