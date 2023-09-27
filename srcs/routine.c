/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:17:05 by anmassy           #+#    #+#             */
/*   Updated: 2023/09/27 22:38:19 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	condition(t_philo *philo, int val)
{
	pthread_mutex_lock(&philo->arg->dead);
	if (val)
		philo->arg->exit_val = val;
	if (philo->arg->exit_val)
	{
		pthread_mutex_unlock(&philo->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->dead);
	return (0);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->m_eat);
	pthread_mutex_lock(&philo->arg->m_stop);
	if ((!condition(philo, 0) && timer() - philo->last_eat > philo->arg->t_die)
		|| philo->arg->n_philo == 1)
	{
		writen(philo, "is dead");
		condition(philo, 1);
	}
	pthread_mutex_unlock(&philo->arg->m_stop);
	pthread_mutex_unlock(&philo->arg->m_eat);
}

void	eat_time(t_philo *philo)
{
	writen(philo, "is eating");
	pthread_mutex_lock(&philo->arg->m_eat);
	philo->last_eat = timer();
	pthread_mutex_unlock(&philo->arg->m_eat);
	ft_usleep(philo->arg->t_eat);
}

void	sleep_think(t_philo *philo)
{
	writen(philo, "is sleeping");
	ft_usleep(philo->arg->t_sleep);
	writen(philo, "is thinking");
}

void	routine(t_philo *philo)
{
	if (!(philo->pos % 2))
		pthread_mutex_lock(&philo->lfork);
	writen(philo, "has taken a fork");
	if (philo->arg->n_philo == 1)
	{
		ft_usleep(philo->arg->t_die);
		return ;
	}
	pthread_mutex_lock(philo->rfork);
	if ((philo->pos % 2))
		pthread_mutex_lock(&philo->lfork);
	writen(philo, "has taken a fork");
	eat_time(philo);
	if ((philo->pos % 2))
		pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	if (!(philo->pos % 2))
		pthread_mutex_unlock(&philo->lfork);
	sleep_think(philo);
}

