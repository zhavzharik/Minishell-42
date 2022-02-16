/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:12:43 by abridger          #+#    #+#             */
/*   Updated: 2022/02/13 02:10:28 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while ((str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy2(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*sorc;

	i = 0;
	dest = (unsigned char *) dst;
	sorc = (unsigned char *) src;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	size_t			len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen((char *) s1);
	str = (char *)malloc(sizeof(char)
			* (size_t)(len_s1 + ft_strlen((char *)s2)) + 1);
	i = 0;
	if (str)
	{
		str = ft_memcpy2(str, s1, len_s1);
		while (i < (unsigned int) ft_strlen((char *) s2))
		{
			str[len_s1] = s2[i];
			i++;
			len_s1++;
		}
		str[len_s1] = '\0';
	}
	return (str);
}

char	*ft_strnstr2(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen((char *) needle);
	if (len == 0 && needle_len > 0)
		return (NULL);
	if (needle_len > (size_t) ft_strlen((char *) haystack))
		return (NULL);
	if (needle_len == 0)
		return ((char *) haystack);
	if (needle_len > len)
		needle_len = len;
	i = 0;
	while (i <= (len - needle_len))
	{
		if ((haystack[0] == needle[0])
			&& (0 == ft_strncmp(haystack, needle, needle_len)))
			return ((char *) haystack);
		i++;
		haystack++;
	}
	return (NULL);
}
