/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:07:23 by jikang            #+#    #+#             */
/*   Updated: 2021/03/15 18:12:07 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		return (printf("argument error!\n"));
	init_table();
	if (init_philos())
		return (printf("malloc error!\n"));
	clean_table();
	return (0);
}
