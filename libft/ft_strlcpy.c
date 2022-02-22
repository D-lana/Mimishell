/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:29:03 by dlana             #+#    #+#             */
/*   Updated: 2022/02/19 14:29:03 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (!dstsize || dstsize < 0)
	{
		return (ft_strlen(src));
	}
	while (i + 1 != dstsize && src[i] != '\0')
	{
		dst[i] = (char) src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
