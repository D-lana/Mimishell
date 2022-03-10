/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeedril <obeedril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:55:00 by dlana             #+#    #+#             */
/*   Updated: 2022/03/10 19:19:41 by obeedril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\r' || str[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			c;
	long long	rezult;

	i = 0;
	c = 1;
	rezult = 0;
	i = ft_space(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c = (c * -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rezult * c < INT_MIN / 10)
			return (-1);
		if (rezult * c > INT_MAX / 10)
			return (-1);
		rezult = rezult * 10 + (str[i] - '0');
		i++;
	}
	return (rezult * c);
}
