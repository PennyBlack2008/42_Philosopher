/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:07:25 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 01:55:30 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

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

	unsigned long	base_time;
	int				eaten_cnt;
	int				is_dead;
	sem_t			*restaurant;
	sem_t			*msg_ctrl;
	sem_t			*forks;
}					t_table;

typedef struct		s_philo
{
	int				idx;
	int				eaten;
	unsigned long	last_meal;
	pthread_t		tid;
}					t_philo;

t_table				g_table;
t_philo				*g_philos;

int					ft_atoi(char *str);
unsigned long		get_time(void);
void				advanced_sleep(unsigned long input);
void				init_table(void);
int					init_philos(void);
void				clean_table(void);
void				*philo_act(void *phi);

#endif
