/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_of_conduct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:07:22 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 18:03:51 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					msg(t_philo *philo, int action)
{
	unsigned long cur;

	sem_wait(g_table.msg_ctrl);
	if (g_table.is_dead)
	{
		sem_post(g_table.msg_ctrl);
		return (1);
	}
	cur = get_time();
	printf("%lu %d ", cur - g_table.base_time, philo->idx);
	if (action == TAKEN_FORK)
		printf("has taken a fork\n");
	else if (action == EAT)
	{
		printf("is eating\n");
		philo->last_meal = cur;
	}
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
	else if (action == DEAD)
		printf("died\n");
	sem_post(g_table.msg_ctrl);
	return (0);
}

int					eat(t_philo *philo)
{
	sem_wait(g_table.restaurant);
	sem_wait(g_table.forks);
	msg(philo, TAKEN_FORK);
	msg(philo, TAKEN_FORK);
	msg(philo, EAT);
	advanced_sleep(g_table.time_to_eat);
	sem_post(g_table.forks);
	sem_post(g_table.restaurant);
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

	philo = (t_philo *)phi;
	while (1)
	{
		if (philo->eaten == g_table.eaten_goal)
			return (NULL);
		if (get_time() - philo->last_meal > g_table.time_to_die)
		{
			msg(philo, DEAD);
			g_table.is_dead = 1;
			return (NULL);
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
