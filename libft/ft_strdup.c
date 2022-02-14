#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (s1[n] != '\0')
	{
		str[n] = s1[n];
		n++;
	}
	str[n] = '\0';
	return (str);
}
