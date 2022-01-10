/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 09:05:22 by abridger          #+#    #+#             */
/*   Updated: 2022/01/10 16:23:05 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++ != '\0')
		len++;
	return (len);
}

int	ft_len_key(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != 61)
	{
		i++;
		len++;
	}
	return (len);
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
