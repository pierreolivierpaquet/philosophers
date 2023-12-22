/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_num_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:51:48 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/28 13:10:47 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_num_lenght(int n)
{
	int	l;

	l = 0;
	if (n <= 0)
		l++;
	while (n != 0)
	{
		n /= 10;
		l++; 
	}
	return (l);
}

int	philo_is_digit(const char c)
{
	if (c >= '0' && c <= '9')
		return (YES);
	return (NO);
}

int	philo_is_whitespace(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (YES);
	return (NO);
}

long long	philo_ascii_to_num(char *n)
{
	long long		result;
	int				sign;
	int				i;

	result = 0;
	i = 0;
	sign = 1;
	while (philo_is_whitespace(n[i]) == YES)
		i++;
	if (n[i] == '+')
		i++;
	else if (n[i] == '-')
		return (FAILURE);
	while (philo_is_digit(n[i]) == YES)
		result = (result * 10) + (n[i++] - '0');
	if (result > INT32_MAX || philo_is_digit(n[i]) || n[i] != '\0')
		return (FAILURE);
	return ((int)(result * sign));
}

char	*philo_num_to_ascii(int n)
{
	char	*result;
	int		l;

	result = NULL;
	l = philo_num_lenght(n);
	result = malloc(sizeof(*result) * (l + 1));
	if (result == NULL)
		return (NULL);
	result[l--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		result[l--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
