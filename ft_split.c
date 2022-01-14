/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:54:43 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 22:54:44 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_go_space(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		if (s[i] != c)
			return (i);
	}
	return (i);
}

static size_t	ft_go_str(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			i++;
		if (s[i] == c)
			return (i);
	}
	if (s[i] == c)
		return (i);
	return (i);
}

static size_t	ft_words_nb(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] && s[i + 1] == c)
			|| (s[i] != c && !s[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

static char	**ft_free_array(char **array, size_t j)
{
	while (j > 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (ft_words_nb(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	len = 0;
	j = 0;
	while (j < ft_words_nb(s, c))
	{
		i = i + len + ft_go_space(&s[i + len], c);
		len = ft_go_str(&s[i], c);
		array[j] = ft_substr(s, i, len);
		if (!array[j])
			return (ft_free_array(array, j));
		j++;
	}
	if (j == ft_words_nb(s, c))
		array[j] = (void *) 0;
	return (array);
}
