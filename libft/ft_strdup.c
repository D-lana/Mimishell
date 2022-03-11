/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:06:40 by dlana             #+#    #+#             */
/*   Updated: 2022/03/11 18:06:41 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str1;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	str1 = (char *)malloc(sizeof(char) * (i + 1));
	if (str1 == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str1[i] = s[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

char	*ft_strdup_start(const char *s, int start)
{
	int		i;
	char	*str1;

	if (s == NULL)
		return (NULL);
	if ((size_t)start >= ft_strlen(s) || start < 0)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0')
		i++;
	str1 = (char *)malloc(sizeof(char) * (i + 1));
	if (str1 == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0')
	{
		str1[i] = s[start + i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
