/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:23 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/28 14:19:19 by anmassy          ###   ########.fr       */
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

void	*ft_memset(void *s, int c, int n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
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

void	ft_usleep(int ms)
{
	long int	time;

	time = timer();
	while (timer() - time < ms)
		usleep(ms / 10);
}
