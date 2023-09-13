/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:17:05 by anmassy           #+#    #+#             */
/*   Updated: 2023/09/13 13:00:46 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	condition(t_philo *philo, int val)
{
	pthread_mutex_lock(&philo->arg->dead);
	if (val)
		philo->arg->value = 1;
	if (philo->arg->value)
	{
		pthread_mutex_unlock(&philo->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->dead);
	return (0);
}

void	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->m_eat);
	pthread_mutex_lock(&philo->arg->m_stop);
	if ((!condition(philo, 0) && timer() - philo->last_eat > philo->arg->t_die)
		|| philo->arg->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->arg->m_eat);
		pthread_mutex_unlock(&philo->arg->m_stop);
		writen(philo, "is dead");
		condition(philo, 1);
	}
	pthread_mutex_unlock(&philo->arg->m_eat);
	pthread_mutex_unlock(&philo->arg->m_stop);
}

void	forkette(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	writen(philo, "has taken a fork");
	if (philo->arg->n_philo == 1)
	{
		ft_usleep(philo->arg->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->rfork);
	writen(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	writen(philo, "is eating");
	pthread_mutex_lock(&philo->arg->m_eat);
	philo->last_eat = timer();
	philo->count++;
	pthread_mutex_unlock(&philo->arg->m_eat);
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
	while (!condition(philo, 0))
	{
		forkette(philo);
		eating(philo);
		dead(philo);
		if (philo->count == philo->arg->n_eat)
		{
			pthread_mutex_lock(&philo->arg->m_stop);
			if (++philo->arg->stop == philo->arg->n_philo)
			{
				pthread_mutex_unlock(&philo->arg->m_stop);
				writen(philo, "FINISH");
				condition(philo, 2);
			}
			pthread_mutex_unlock(&philo->arg->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}
