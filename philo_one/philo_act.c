/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:52:07 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 03:16:52 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					msg(t_philo *philo, int action)
{
	unsigned long cur;

	pthread_mutex_lock(&g_table.msg_ctrl);
	if (g_table.is_dead == 1)
	{
		pthread_mutex_unlock(&g_table.msg_ctrl);
		return (1);
	}
	cur = get_time();
	printf("%lu %d ", cur - g_table.base_time, philo->idx);
	if (action == TAKEN_FORK)
		printf("has taken a fork\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
	else if (action == DEAD)
	{
		printf("died\n");
		g_table.is_dead = 1;
	}
	pthread_mutex_unlock(&g_table.msg_ctrl);
	return (0);
}

int					eat(t_philo *philo)
{
	pthread_mutex_lock(&g_table.fork[philo->fork1]);
	msg(philo, TAKEN_FORK);
	pthread_mutex_lock(&g_table.fork[philo->fork2]);
	msg(philo, TAKEN_FORK);
	msg(philo, EAT);
	philo->last_meal = get_time();
	advanced_sleep(g_table.time_to_eat);
	pthread_mutex_unlock(&g_table.fork[philo->fork1]);
	pthread_mutex_unlock(&g_table.fork[philo->fork2]);
	philo->eaten++;
	if (philo->eaten == g_table.eaten_goal)
	{
		g_table.eaten_cnt++;
		return (1);
	}
	return (0);
}

void				*monitor(void *phi)
{
	t_philo			*philo;
	unsigned long	cur;

	philo = (t_philo *)phi;
	while (1)
	{
		if (philo->eaten == g_table.eaten_goal)
			break ;
		cur = get_time();
		if (cur - philo->last_meal > g_table.time_to_die)
		{
			msg(philo, DEAD);
			break ;
		}
		advanced_sleep(1);
	}
	return (NULL);
}

void				*philo_act(void *phi)
{
	t_philo			*philo;
	pthread_t		tid;

	philo = (t_philo *)phi;
	if ((philo->idx % 2 == 0))
		advanced_sleep(1);
	pthread_create(&tid, NULL, monitor, philo);
	while (1)
	{
		if (eat(philo))
			break ;
		if (msg(philo, SLEEP))
			break ;
		advanced_sleep(g_table.time_to_sleep);
		if (msg(philo, THINK))
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
