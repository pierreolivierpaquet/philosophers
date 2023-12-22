/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:46:10 by ppaquet           #+#    #+#             */
/*   Updated: 2023/09/06 10:29:21 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_env	*philo_env_init(void)
{
	t_philo_env	*new_env;

	new_env = NULL;
	new_env = malloc(sizeof(*new_env));
	if (new_env == NULL)
		return (NULL);
	new_env->must_eat_amt = DEFAULT;
	new_env->philo_amt = DEFAULT;
	new_env->time_to_die = DEFAULT;
	new_env->time_to_eat = DEFAULT;
	new_env->time_to_sleep = DEFAULT;
	new_env->chopsticks = NULL;
	new_env->philo = NULL;
	new_env->death = NULL;
	new_env->ac = DEFAULT;
	new_env->av = NULL;
	return (new_env);
}

int	philo_env_mutexes_init(t_philo_env *env)
{
	if (env == NULL)
		return (FAILURE);
	if (pthread_mutex_init(&env->death_mutex, NULL) != SUCCESS)
	{
		philo_err_msg("Initializing death_mutex.", FD_ERR);
		return (FAILURE);
	}
	if (pthread_mutex_init(&env->print_mutex, NULL) != SUCCESS)
	{
		philo_err_msg("Initializing print_mutex.", FD_ERR);
		if (pthread_mutex_destroy(&env->death_mutex) != SUCCESS)
			philo_err_msg("Destroying death_mutex.", FD_ERR);
		return (FAILURE);
	}
	if (pthread_mutex_init(&env->csticks_mutex, NULL) != SUCCESS)
	{
		philo_err_msg("Initializing cstcks_mutex.", FD_ERR);
		if (pthread_mutex_destroy(&env->death_mutex) != SUCCESS
			|| pthread_mutex_destroy(&env->print_mutex) != SUCCESS)
			philo_err_msg("Destroying MUTEX(es).", FD_ERR);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_philo_env	*philo_env_pull(void)
{
	static t_philo_env	*philosophers_env;

	if (philosophers_env == NULL)
	{
		philosophers_env = philo_env_init();
		if (philosophers_env != NULL)
		{
			if (philo_env_mutexes_init(philosophers_env) == FAILURE)
			{
				philo_env_free(&philosophers_env);
				return (NULL);
			}
		}
		return (philosophers_env);
	}
	else if (philosophers_env != NULL)
		return (philosophers_env);
	return (NULL);
}

int	philo_environment(int ac, char **av)
{
	t_philo_env	*env;

	if (ac == 0 || av == NULL)
		return (FAILURE);
	env = NULL;
	env = philo_env_pull();
	if (env == NULL)
		return (philo_err_msg("Creating environment.", FD_ERR));
	philo_args_retain(env, ac, av);
	if (philo_args_parse(env) == FAILURE)
	{
		philo_env_free(&env);
		return (FAILURE);
	}
	return (SUCCESS);
}
