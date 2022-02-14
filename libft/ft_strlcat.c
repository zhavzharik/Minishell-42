#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = ft_strlen(dst);
	j = ft_strlen((char*)src);
	k = 0;
	if (i >= size)
		return (j + size);
	else
		j = j + i;
	while (src[k] != '\0' && size - 1 > k + i)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (j);
}
