#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	int			i;
	size_t		count;

	i = 0;
	count = 1;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	if (s[0] == c)
		count--;
	if (s[i - 1] == c)
		count--;
	return (count);
}

static size_t	ft_len_substr(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	x;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_count_words(s, c) > i)
	{
		while (s[j] == c)
			j++;
		x = ft_len_substr(s + j, c);
		arr[i] = ft_substr(s, j, x);
		if (arr[i] == NULL)
			return (ft_free(arr, i));
		i++;
		j = j + x;
	}
	arr[i] = NULL;
	return (arr);
}
