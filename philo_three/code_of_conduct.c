/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_of_conduct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:24:44 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 03:03:00 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					msg(t_philo *philo, int action)
{
	unsigned long	cur;

	sem_wait(g_table.msg_ctrl);
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
		exit(1);
	}
	sem_post(g_table.msg_ctrl);
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
			msg(philo, DEAD);
		advanced_sleep(1);
	}
	return (NULL);
}

int					eat(t_philo *philo)
{
	sem_wait(g_table.restaurant);
	sem_wait(g_table.forks);
	msg(philo, TAKEN_FORK);
	msg(philo, TAKEN_FORK);
	msg(philo, EAT);
	philo->last_meal = get_time();
	advanced_sleep(g_table.time_to_eat);
	sem_post(g_table.forks);
	sem_post(g_table.restaurant);
	philo->eaten++;
	if (philo->eaten == g_table.eaten_goal)
		return (1);
	return (0);
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
