/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:28:33 by dlana             #+#    #+#             */
/*   Updated: 2022/03/07 19:43:33 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cases(char *sign, int *n);
static int	ft_merlin(int n);

char	*ft_itoa(int n)
{
	int		len;
	char	sign;
	char	*trans_int;

	trans_int = ft_cases(&sign, &n);
	if (!trans_int)
	{
		len = ft_merlin(n);
		trans_int = (char *)malloc(sizeof(char) * (sign + len + 1));
		if (!trans_int)
			return (NULL);
		if (sign)
			trans_int[0] = '-';
		trans_int[sign + len] = '\0';
		while (len > 0)
		{
			len--;
			trans_int[sign + len] = n % 10 + '0';
			n = n / 10;
		}
	}
	return (trans_int);
}

static char	*ft_cases(char *sign, int *n)
{
	if (*n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (*n == 0)
		return (ft_strdup("0"));
	*sign = 0;
	if (*n < 0)
	{
		*n = -*n;
		*sign = 1;
	}
	return (NULL);
}

static int	ft_merlin(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}
