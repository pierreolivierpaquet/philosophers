/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:54:36 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 15:22:04 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*philo_philosophers_free(t_philosopher **philo, int index)
{
	if (philo == NULL || *philo == NULL)
		return (NULL);
	while (--index >= 0)
	{
		(*philo)[index].cs1 = NULL;
		(*philo)[index].cs2 = NULL;
		(*philo)[index].d_line = DEFAULT;
		(*philo)[index].env = NULL;
		(*philo)[index].state = DEFAULT;
		(*philo)[index].t_t_die = DEFAULT;
		(*philo)[index].t_t_eat = DEFAULT;
		(*philo)[index].t_t_slp = DEFAULT;
		(*philo)[index].tag = DEFAULT;
	}
	free(*philo);
	*philo = NULL;
	philo = NULL;
	return (NULL);
}

void	philo_chopsticks_mutex_destroy(t_cstick **cs, int index, int *status)
{
	if ((*cs)[index].state == AVBL)
	{
		if (pthread_mutex_destroy(&(*cs)[index].cs_mutex) != SUCCESS)
		{
			if (*status == SUCCESS)
				*status = FAILURE;
			philo_err_msg("Destroying c.sticks MUTEX(ES).", FD_ERR);
		}
	}
	return ;
}

t_cstick	*philo_chopsticks_free(t_cstick **cs, int index, int *status)
{
	if (cs == NULL || *cs == NULL)
		return (NULL);
	while (--index >= 0)
	{
		philo_chopsticks_mutex_destroy(cs, index, status);
		(*cs)[index].state = DEFAULT;
	}
	free(*cs);
	*cs = NULL;
	cs = NULL;
	return (NULL);
}

int	philo_env_mutex_destroy(t_philo_env **env, int *status)
{
	if ((*env)->av == NULL)
		return (*status);
	if (pthread_mutex_destroy(&(*env)->print_mutex))
	{
		philo_err_msg("Destroying print MUTEX.", FD_ERR);
		if (*status == SUCCESS)
			*status = FAILURE;
	}
	if (pthread_mutex_destroy(&(*env)->death_mutex) != SUCCESS)
	{
		philo_err_msg("Destroying death MUTEX.", FD_ERR);
		if (*status == SUCCESS)
			*status = FAILURE;
	}
	if (pthread_mutex_destroy(&(*env)->csticks_mutex) != SUCCESS)
	{
		philo_err_msg("Destroying csticks MUTEX.", FD_ERR);
		if (*status == SUCCESS)
			*status = FAILURE;
	}
	return (SUCCESS);
}

int	philo_env_free(t_philo_env **env)
{
	int	free_status;

	free_status = SUCCESS;
	if (env == NULL || *env == NULL)
		return (free_status);
	philo_env_mutex_destroy(env, &free_status);
	(*env)->philo = philo_philosophers_free(&(*env)->philo, (*env)->philo_amt);
	(*env)->chopsticks = philo_chopsticks_free(&(*env)->chopsticks, \
		(*env)->philo_amt, &free_status);
	(*env)->death = NULL;
	(*env)->must_eat_amt = 0;
	(*env)->ac = 0;
	(*env)->av = NULL;
	(*env)->philo_amt = 0;
	(*env)->time_to_die = 0;
	(*env)->time_to_eat = 0;
	(*env)->time_to_sleep = 0;
	free(*env);
	*env = NULL;
	env = NULL;
	return (free_status);
}
