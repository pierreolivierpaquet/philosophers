/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:56:18 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/23 10:11:37 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_nullify(void *memory, unsigned long long n)
{
	if (n <= 0)
		return (FAILURE);
	memory = memset(memory, 0, n);
	return (SUCCESS);
}

void	*philo_alloc(bool type, int n, int size)
{
	void	*temp;
	size_t	mem;

	mem = (size_t)size * (size_t)n;
	temp = NULL;
	temp = malloc(mem);
	if (temp == NULL)
		return (NULL);
	if (type == CALLOC)
		philo_nullify(temp, mem);
	return (temp);
}
