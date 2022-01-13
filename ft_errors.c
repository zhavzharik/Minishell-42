/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:32:20 by abridger          #+#    #+#             */
/*   Updated: 2022/01/13 16:53:40 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_err_message(char *str)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
// int	ft_error(int errnum, t_data *data, char *str)
// {
// 	char	*str_err;

// 	errnum = errno;
// 	printf("ERRNUM %d\n", errnum);
// 	printf("ERRNO %d\n", errno);
// 	str_err = strerror(errnum);
// 	ft_data_clear(data);
// 	write(STDERR_FILENO, str, ft_strlen(str));
// 	write(STDERR_FILENO, str_err, ft_strlen(str_err));
// 	write(STDERR_FILENO, "\n", 1);
// 	return (1);
// }

int	ft_error(int errnum, t_data *data, char *str)
{
	// char	*str_err;

	// str_err = "error";
	if (errnum == 1)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		// write(STDERR_FILENO, str_err, ft_strlen(str_err));
		write(STDERR_FILENO, "\n", 1);
		ft_data_clear(data);
		return (1);
	}
	return (1);
}
