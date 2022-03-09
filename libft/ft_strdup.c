#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str1;

	if (s == NULL)
		return (NULL);
	i = 0;
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
