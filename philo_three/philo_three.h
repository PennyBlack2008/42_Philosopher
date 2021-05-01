/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:24:53 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 02:12:42 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define ERR 1

enum				e_action
{
	TAKEN_FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef struct		s_table
{
	int				philo_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				eaten_goal;
	int				eaten_cnt;

	unsigned long	base_time;
	sem_t			*restaurant;
	sem_t			*msg_ctrl;
	sem_t			*forks;
}					t_table;

typedef struct		s_philo
{
	int				idx;
	int				eaten;
	unsigned long	last_meal;
	pid_t			pid;
}					t_philo;

t_table				g_table;
t_philo				*g_philos;

void				*philo_act(void *phi);
void				process_monitor(void);
int					init_table(void);
int					init_philos(void);
void				clean_table(void);
int					ft_atoi(char *str);
unsigned long		get_time(void);
void				advanced_sleep(unsigned long input);

#endif
