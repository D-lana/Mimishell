#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *) s1;
	ss2 = (unsigned char *) s2;
	while ((*ss1 != '\0' || *ss2 != '\0') && n > 0)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
		n--;
	}
	if ((*ss1 != '\0' || *ss2 != '\0') && n > 0)
		return (*ss1 - *ss2);
	return (0);
}
