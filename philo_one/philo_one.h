/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:52:09 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 18:01:48 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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
	int				is_dead;
	unsigned long	base_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	msg_ctrl;
}					t_table;

typedef struct		s_philo
{
	int				idx;
	int				fork1;
	int				fork2;
	int				eaten;
	unsigned long	last_meal;
	pthread_t		tid;
}					t_philo;

t_table				g_table;
t_philo				*g_philos;

void				init_table(void);
void				init_philos(void);
void				clean_table(void);
void				*philo_act(void *phi);
int					ft_atoi(char *str);
unsigned long		get_time(void);
void				advanced_sleep(unsigned long input);

#endif
