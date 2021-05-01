/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:24:55 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 03:09:50 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		kill_processes(void)
{
	int i;

	i = 0;
	while (i < g_table.philo_num)
	{
		kill(g_philos[i].pid, SIGKILL);
		i++;
	}
}

void		process_monitor(void)
{
	int		i;
	int		exit_status;

	while (1)
	{
		i = -1;
		while (++i < g_table.philo_num)
		{
			exit_status = -1;
			waitpid(g_philos[i].pid, &exit_status, WNOHANG);
			if (exit_status == 0 && ++g_table.eaten_cnt)
			{
				if (g_table.eaten_cnt == g_table.philo_num)
					break ;
			}
			if (exit_status == 256)
				break ;
		}
		if (i != g_table.philo_num)
		{
			kill_processes();
			break ;
		}
		advanced_sleep(1);
	}
}
