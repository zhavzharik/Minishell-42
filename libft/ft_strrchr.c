#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	while (n >= 0)
	{
		if (s[n] == (unsigned char)c)
			return ((char *)s + n);
		n--;
	}
	return (NULL);
}
