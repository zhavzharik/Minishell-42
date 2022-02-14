/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:32:20 by abridger          #+#    #+#             */
/*   Updated: 2022/02/12 23:48:07 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	put_err_message(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_error(t_shell *data, char *str)
{
	char	*str_err;

	data->exit_status = errno;
	str_err = strerror(errno);
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	write(STDERR_FILENO, "\n", 1);
	ft_str_clear(&str);
	return (1);
}

char	*ft_two_colon(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = NULL;
	str2 = NULL;
	str3 = NULL;
	if (s1)
		str1 = ft_strjoin2(s1, ": ");
	if (s2)
		str2 = ft_strjoin2(s2, ": ");
	else
		return (str1);
	if (s1 && s2)
	{
		str3 = ft_strjoin2(str1, str2);
		free(str1);
		free(str2);
	}
	return (str3);
}

char	*ft_one_colon(char *s1)
{
	char	*str1;

	str1 = NULL;
	if (s1)
		str1 = ft_strjoin2(s1, ": ");
	return (str1);
}
