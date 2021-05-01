/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:24:52 by jikang            #+#    #+#             */
/*   Updated: 2021/03/15 20:35:03 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	parse(char *argv[])
{
	if ((g_table.philo_num = ft_atoi(argv[1])) <= 1 ||
		(g_table.time_to_die = ft_atoi(argv[2])) <= 0 ||
		(g_table.time_to_eat = ft_atoi(argv[3])) <= 0 ||
		(g_table.time_to_sleep = ft_atoi(argv[4])) <= 0)
		return (ERR);
	if (argv[5])
	{
		if ((g_table.eaten_goal = ft_atoi(argv[5])) <= 0)
			return (ERR);
	}
	else
		g_table.eaten_goal = -1;
	return (0);
}

int	main(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("arguments error!\n"));
	init_table();
	if (init_philos())
		return (ERR);
	clean_table();
	return (0);
}
