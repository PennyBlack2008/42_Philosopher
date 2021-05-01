/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:52:12 by jikang            #+#    #+#             */
/*   Updated: 2021/03/16 01:05:57 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_atoi(char *str)
{
	int num;
	int i;
	int sign;

	num = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

unsigned long		get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void				advanced_sleep(unsigned long input)
{
	unsigned long	base;
	unsigned long	cur;

	base = get_time();
	while (1)
	{
		cur = get_time();
		if (cur - base > input)
			return ;
		usleep(500);
	}
}
