#include "libft.h"

char	*ft_strcpy(char *dest, char *source)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (source)
		while (source[i])
			dest[j++] = source[i++];
	dest[j] = '\0';
	return (dest);
}
