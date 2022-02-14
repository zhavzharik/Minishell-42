/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:43:39 by abridger          #+#    #+#             */
/*   Updated: 2022/01/23 18:13:22 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_builtin	*create_array_function(void)
{
	t_builtin	*array_func;

	array_func = NULL;
	array_func = (t_builtin *)malloc(sizeof(t_builtin) * 7);
	(array_func)[0] = &ft_exec_echo;
	(array_func)[1] = &ft_exec_cd;
	(array_func)[2] = &ft_exec_pwd;
	(array_func)[3] = &ft_exec_export;
	(array_func)[4] = &ft_exec_unset;
	(array_func)[5] = &ft_exec_exit;
	(array_func)[6] = &ft_exec_env;
	return (array_func);
}

void	print_argv(char **str, int indx)
{
	int	i;

	i = indx;
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		write(1, " ", 1);
		i++;
	}
	if (indx == 1)
		write(1, "\n", 1);
}

int	ft_exec_echo(t_shell *data, t_info *curr)
{

	(void)data;
	if (curr->nb_cmd == 0)
	{
		if (curr->argv[1] && !ft_strcmp2(curr->argv[1], "-n"))
			print_argv(curr->argv, 2);
		else
			print_argv(curr->argv, 1);
	}
	data->exit_status = 0;
	return (0);
}

int	ft_exec_pwd(t_shell *data, t_info *curr)
{
	char	*str;
	char	buf[1024];

	(void) data;
	str = getcwd(buf, sizeof(buf));
	if (curr->nb_cmd == 2 && str)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	data->exit_status = 0;
	return (0);
}
