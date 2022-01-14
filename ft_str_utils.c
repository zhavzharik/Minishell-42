/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:55:03 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 23:30:23 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)s1);
	str = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	if (str)
	{
		while (i < len)
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
	if (!str)
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (start >= s_len)
		len = 0;
	if (len > s_len)
		len = s_len;
	str = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	if (!str)
		return (NULL);
	if (str)
	{
		while (i < len)
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	size_t			len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen((char *) s1);
	str = (char *)malloc(sizeof(char) * (len_s1 + ft_strlen((char *) s2)) + 1);
	i = 0;
	if (str)
	{
		str = ft_memcpy(str, s1, len_s1);
		while (i < (unsigned int) ft_strlen((char *) s2))
		{
			str[len_s1] = s2[i];
			i++;
			len_s1++;
		}
		str[len_s1] = '\0';
	}
	return (str);
	if (!str)
		return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
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
