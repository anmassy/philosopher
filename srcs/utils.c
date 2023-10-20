/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:23 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/09 17:05:38 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char *s)
{
	int	sign;
	int	nb;
	int	i;

	sign = 1;
	nb = 0;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i] - 48);
		i++;
	}
	return (sign * nb);
}

long int	timer(void)
{
	struct timeval	the_time;
	long int		time;

	gettimeofday(&the_time, NULL);
	time = (the_time.tv_sec * 1000) + (the_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int	time;
	int			mili;

	time = timer();
	if (philo->arg->t_sleep <= 110)
		mili = ms + 8;
	else
		mili = ms;
	while (timer() - time <= mili)
	{
		usleep(ms / 10);
		check_death(philo);
	}
}
