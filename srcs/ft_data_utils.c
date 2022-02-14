/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:01:41 by abridger          #+#    #+#             */
/*   Updated: 2022/02/13 01:28:09 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != 61)
	{
		i++;
	}
	return (i);
}

int	ft_len_value(char *str)
{
	int	len;
	int	len_key;
	int	i;

	len = ft_strlen(str);
	len_key = ft_len_key(str);
	i = 1 + len_key;
	if (len > len_key)
	{
		while (str[i] != '\0' && i < len)
		{
			i++;
		}
		return (i - 1 - len_key);
	}
	else
		return (0);
}

int	ft_height_array(char **array)
{
	int		i;
	char	**line;

	i = 0;
	line = array;
	while (line[i])
			i++;
	return (i);
}
