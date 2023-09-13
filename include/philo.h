/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniezgod <aniezgod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:28:45 by anmassy           #+#    #+#             */
/*   Updated: 2023/09/12 19:23:25 by aniezgod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* toute les commandes avec pthread */
# include <pthread.h>

/* printf */
# include <stdio.h>

/* malloc, free */
# include <stdlib.h>

/* write */
# include <unistd.h>
# include <stdbool.h>

/* time */
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				pos;
	int				count;
	long int		last_eat;
	struct s_data	*arg;
	pthread_t		thread;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	lfork;
}	t_philo;

typedef struct s_data
{
	int				stop;
	int				value;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	writing;
	pthread_mutex_t	m_eat;
	pthread_mutex_t m_stop;
	pthread_mutex_t dead;
	}	t_data;

/* check.c */
int			check_overflow(char *arg);
int			check_arg(char **av);

/* init.c */
int			init_mutex(t_data *d);
int			init_val(t_data *d, char **av);
int			init_philo(t_data *d);
int			create_thread(t_data *d);

/* routine.c */
void		dead(t_philo *philo);
void		writen(t_philo *philo, char *msg);
void		forkette(t_philo *philo);
void		eating(t_philo *philo);
void		*routine(void *ph);

/* utils.c */
int			ft_strlen(char *s);
void		*ft_memset(void *s, int c, int n);
int			ft_atoi(char *s);
long int	timer(void);
void		ft_usleep(int ms);

#endif
