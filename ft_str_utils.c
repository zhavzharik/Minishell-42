/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:55:03 by abridger          #+#    #+#             */
/*   Updated: 2022/01/10 18:16:24 by abridger         ###   ########.fr       */
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
