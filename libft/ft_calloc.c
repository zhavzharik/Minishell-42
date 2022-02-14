#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	buff;
	void	*str;

	buff = (count * size);
	str = malloc(buff);
	if (!str)
		return (NULL);
	ft_bzero(str, buff);
	return ((void *)str);
}
