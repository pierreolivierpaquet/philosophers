/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:08:34 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 15:29:46 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_launching(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->must_eat == 0)
		return (NULL);
	if (philo->tag % 2 == 0)
	{
		philo->d_line += philo_fetch_time();
		philo_thinking(philo);
		philo_usleep(philo, (philo->t_t_eat));
	}
	else
		philo->d_line += philo_fetch_time();
	while (philo_death_check(philo) == SUCCESS)
	{
		if ((philo_eating(philo) != SUCCESS)
			|| (philo_sleeping(philo) != SUCCESS)
			|| (philo_thinking(philo) != SUCCESS))
			break ;
	}
	return (NULL);
}

int	philo_thread_init(t_philo_env *env)
{
	int	i;
	int	k;

	i = -1;
	k = env->philo_amt;
	if (env == NULL)
		return (FAILURE);
	while (++i < k)
	{
		if (pthread_create(&env->philo[i].thd_id, NULL, &philo_launching, \
		&env->philo[i]) != 0)
		{
			philo_err_msg("Launching philosophers threads.", FD_ERR);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	philo_thread_join(t_philo_env *env)
{
	int	i;

	i = -1;
	while (++i < env->philo_amt)
	{
		if (pthread_join(env->philo[i].thd_id, NULL) != 0)
		{
			philo_err_msg("Joining philosophers threads.", FD_ERR);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
