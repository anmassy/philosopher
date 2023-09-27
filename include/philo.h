/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:28:45 by anmassy           #+#    #+#             */
/*   Updated: 2023/09/27 20:49:05 by anmassy          ###   ########.fr       */
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
	int				count_eat;
	long int		last_eat;
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	struct s_data	*arg;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long int		t_start;
	int				exit_val;
	int				stop;
	pthread_mutex_t	writing;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
	t_philo			*philo;
}	t_data;

/* check.c */
int			check_overflow(char *arg);
int			check_arg(char **av);

/* init.c */
int			init_mutex(t_data *d);
int			init_val(t_data *d, char **av);
int			init_philo(t_data *d);
int			create_philo(t_data *d);
void		*start_dinner(void *ph);

/* routine.c */
int			condition(t_philo *philo, int val);
void		check_death(t_philo *philo);
void		eat_time(t_philo *philo);
void		sleep_think(t_philo *philo);
void		routine(t_philo	*philo);

/* utils.c */
int			ft_strlen(char *s);
int			ft_atoi(char *s);
long int	timer(void);
void		ft_usleep(int ms);

/* philo.c */
void		writen(t_philo *philo, char *msg);
void		ft_destroy(t_data *d);

#endif
