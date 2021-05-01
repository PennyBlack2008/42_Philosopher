/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:52:14 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 18:02:07 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_table(void)
{
	int	i;

	i = 0;
	g_table.base_time = get_time();
	g_table.is_dead = 0;
	g_table.eaten_cnt = 0;
	while (i < g_table.philo_num)
	{
		pthread_mutex_init(&g_table.fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&g_table.msg_ctrl, NULL);
}

void	init_philos(void)
{
	int	i;

	i = 0;
	while (i < g_table.philo_num)
	{
		g_philos[i].idx = i + 1;
		g_philos[i].last_meal = g_table.base_time;
		g_philos[i].eaten = 0;
		g_philos[i].fork1 = i - 1;
		if (g_philos[i].fork1 < 0)
			g_philos[i].fork1 = g_table.philo_num - 1;
		g_philos[i].fork2 = i;
		pthread_create(&g_philos[i].tid, NULL, philo_act, &g_philos[i]);
		i++;
	}
	i = 0;
	while (i < g_table.philo_num)
	{
		pthread_join(g_philos[i].tid, NULL);
		i++;
	}
}

void	clean_table(void)
{
	int	i;

	i = 0;
	while (i < g_table.philo_num)
	{
		pthread_mutex_destroy(&g_table.fork[i]);
		i++;
	}
	pthread_mutex_destroy(&g_table.msg_ctrl);
	free(g_philos);
	g_philos = NULL;
}
