/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:21:08 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 15:22:13 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_err_msg(const char *msg, int fd)
{
	if (msg == NULL)
	{
		philo_putendl_fd("\033[31m[ERROR]\033[0m", STDERR_FILENO);
		return (FAILURE);
	}
	philo_putstr_fd("\033[31m[ERROR]\033[0m ", fd);
	philo_putendl_fd(msg, fd);
	return (FAILURE);
}

int	philo_msg(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->env->print_mutex);
	if (philo_death_check(philo) == SUCCESS
		|| (philo_death_check(philo) == FAILURE && philo->state == DEAD))
	{
		printf("%lli \033[1m%i\033[0m %s\n", philo_fetch_time(), \
			philo->tag, message);
	}
	pthread_mutex_unlock(&philo->env->print_mutex);
	return (SUCCESS);
}
