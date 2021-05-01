/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:24:59 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 03:04:30 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			init_table(void)
{
	g_table.restaurant = sem_open("/sem_one", O_CREAT | O_EXCL, 0777,
									g_table.philo_num / 2);
	g_table.msg_ctrl = sem_open("/sem_two", O_CREAT | O_EXCL, 0777, 1);
	g_table.forks = sem_open("/sem_three", O_CREAT | O_EXCL, 0777,
									g_table.philo_num);
	g_table.base_time = get_time();
	g_table.eaten_cnt = 0;
	sem_unlink("/sem_one");
	sem_unlink("/sem_two");
	sem_unlink("/sem_three");
	return (0);
}

int			init_philos(void)
{
	int		i;

	i = 0;
	if (!(g_philos = (t_philo *)malloc(sizeof(t_philo) * g_table.philo_num)))
		return (ERR);
	while (i < g_table.philo_num)
	{
		g_philos[i].idx = i + 1;
		g_philos[i].last_meal = get_time();
		g_philos[i].eaten = 0;
		g_philos[i].pid = fork();
		if (g_philos[i].pid == 0)
			break ;
		i++;
	}
	if (i != g_table.philo_num)
	{
		philo_act(&g_philos[i]);
		exit(0);
	}
	else
		process_monitor();
	return (0);
}

void		clean_table(void)
{
	sem_close(g_table.restaurant);
	sem_close(g_table.msg_ctrl);
	sem_close(g_table.forks);
	free(g_philos);
	g_philos = NULL;
}
