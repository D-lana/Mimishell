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
