#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		length;
	int		index;

	if (!s1 || !s2)
		return (0);
	length = 0;
	index = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (result == 0)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	while (*(s1 + length))
		result[index++] = s1[length++];
	length = 0;
	while (*(s2 + length))
		result[index++] = s2[length++];
	result[index] = '\0';
	free(s1);
	free(s2);
	return (result);
}
