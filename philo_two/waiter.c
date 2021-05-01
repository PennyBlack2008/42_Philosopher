/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:07:20 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 18:03:14 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	init_table(void)
{
	g_table.is_dead = 0;
	g_table.base_time = get_time();
	g_table.eaten_cnt = 0;
	g_table.restaurant = sem_open("/sem_one", O_CREAT | O_EXCL, 0777,
		g_table.philo_num / 2);
	g_table.msg_ctrl = sem_open("/sem_two", O_CREAT | O_EXCL, 0777, 1);
	g_table.forks = sem_open("/sem_three", O_CREAT | O_EXCL, 0777,
						g_table.philo_num);
	sem_unlink("/sem_one");
	sem_unlink("/sem_two");
	sem_unlink("/sem_three");
}

int		init_philos(void)
{
	int	i;

	i = 0;
	if (!(g_philos = (t_philo *)malloc(sizeof(t_philo) * g_table.philo_num)))
		return (ERR);
	while (i < g_table.philo_num)
	{
		g_philos[i].idx = i + 1;
		g_philos[i].eaten = 0;
		g_philos[i].last_meal = g_table.base_time;
		pthread_create(&g_philos[i].tid, NULL, philo_act, &g_philos[i]);
		i++;
	}
	i = 0;
	while (i < g_table.philo_num)
	{
		pthread_join(g_philos[i].tid, NULL);
		i++;
	}
	return (0);
}

void	clean_table(void)
{
	sem_close(g_table.restaurant);
	sem_close(g_table.msg_ctrl);
	sem_close(g_table.forks);
	free(g_philos);
	g_philos = NULL;
}
