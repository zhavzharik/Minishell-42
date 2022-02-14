#include "libft.h"

static int	ft_c(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i++] == c)
			return (0);
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen((char*)s1);
	while (ft_c(set, s1[start]) == 0)
		start++;
	while (ft_c(set, s1[end - 1]) == 0)
		end--;
	str = ft_substr(s1, start, end - start);
	return (str);
}
