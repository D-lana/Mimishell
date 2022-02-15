#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s2;
	char	c2;

	s2 = (char *) s;
	c2 = (char) c;
	while (*s2 != '\0')
	{
		if (*s2 == c2)
			return (s2);
		s2++;
	}
	if (*s2 == '\0' && c == '\0')
		return (s2);
	return (NULL);
}
