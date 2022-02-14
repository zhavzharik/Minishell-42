/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:23:47 by abridger          #+#    #+#             */
/*   Updated: 2022/01/27 16:32:30 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_right_digit(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] != '\0')
	{
		check = ft_isdigit(str[i]);
		if (check == 0)
			return (check);
		i++;
	}
	return (check);
}

int	ft_err_exit(t_shell *data, char *str, int flag)
{
	char	*part_str;
	char	*err;

	part_str = NULL;
	err = NULL;
	if (flag == 1)
	{
		data->exit_status = 255;
		part_str = ft_two_colon("exit", str);
		err = ft_strjoin2(part_str, "numeric argument required");
	}
	else if (flag == 2)
	{
		data->exit_status = 1;
		part_str = ft_one_colon("exit");
		err = ft_strjoin2(part_str, "too many arguments");
	}
	write(STDERR_FILENO, "exit\n", ft_strlen("exit\n"));
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, "\n", 1);
	ft_str_clear(&part_str);
	ft_str_clear(&err);
	if (flag == 1)
		exit(data->exit_status);
	return (1);
}

int	ft_right_exit(t_shell *data, t_info *curr, int flag)
{
	if (flag == 1)
		data->exit_status = ft_atoi(curr->argv[1]);
	else if (flag == 2)
		data->exit_status = 0;
	if (data->count == 1)
	{
		write(1, curr->argv[0], ft_strlen(curr->argv[0]));
		write(1, "\n", 1);
		exit(data->exit_status);
	}
	return (0);
}

int	ft_exec_exit(t_shell *data, t_info *curr)
{
	int	size;

	size = ft_height_array(curr->argv);
	if (curr->nb_cmd == 5)
	{
		if (size > 1)
		{
			if (!ft_right_digit(curr->argv[1]))
				return (ft_err_exit(data, curr->argv[1], 1));
			else if (ft_right_digit(curr->argv[1]) && size > 2)
				return (ft_err_exit(data, curr->argv[1], 2));
			else if (ft_right_digit(curr->argv[1]) && size == 2)
				return (ft_right_exit(data, curr, 1));
		}
		else if (size == 1)
			return (ft_right_exit(data, curr, 2));
	}
	return (0);
}
