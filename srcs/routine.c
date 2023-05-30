/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:17:05 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/30 17:34:34 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead(t_philo *philo)
{
	// printf("time =%ld\n", timer());
	// printf("last =%ld\n", philo->last_eat);
	if (timer() - philo->last_eat > philo->arg->t_die)
	{
		writen(philo, "is dead");
		return (0);
	}
	return (1);
}

void	writen(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->arg->writing);
	printf("%ld %d %s\n", timer() - philo->arg->t_start, philo->pos, msg);
	pthread_mutex_unlock(&philo->arg->writing);
}

void	forkette(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	writen(philo, "has taken a fork");
	if (philo->arg->n_philo == 1)
		return ;
	pthread_mutex_lock(philo->rfork);
	writen(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	writen(philo, "is eating");
	// philo->last_eat = timer();
	// philo->count++;
	ft_usleep(philo->arg->t_eat);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
	writen(philo, "is sleeping");
	ft_usleep(philo->arg->t_sleep);
	writen(philo, "is thinking");
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->pos % 2 == 0)
		ft_usleep(philo->arg->t_eat / 10);
	while (!dead(philo))
	{
		forkette(philo);
		eating(philo);
		// if (philo->count == philo->arg->n_eat)
		// {
		// 	writen(philo, "finish");
		// 	return (NULL);
		// }
	}
	return (NULL);
}
