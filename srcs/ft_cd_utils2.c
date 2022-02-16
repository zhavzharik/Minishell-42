/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:32:44 by abridger          #+#    #+#             */
/*   Updated: 2022/02/16 13:30:40 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_no_oldpwd(t_shell *data, char *str)
{
	data->exit_status = 1;
	write(STDERR_FILENO, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

void	ft_write_str(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
}

int	ft_print_dir(t_shell *data, char *curr_pwd)
{
	char	*str;
	t_env	*tmp;
	int		check;

	tmp = data->env;
	check = 0;
	while (tmp && check == 0)
	{
		if (0 == ft_strcmp2(tmp->key, "OLDPWD"))
		{
			str = ft_strdup(tmp->value);
			check = 1;
		}
		tmp = tmp->next;
	}
	if (check == 0)
		return (ft_no_oldpwd(data, "OLDPWD not set\n"));
	else
	{
		chdir(str);
		ft_change_pwd_env(data, curr_pwd, str);
	}
	ft_write_str(str);
	return (0);
}

int	ft_err_option(t_shell *data, char *str)
{
	data->exit_status = 1;
	write(STDERR_FILENO, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(STDERR_FILENO, str, 2);
	write(STDERR_FILENO, ": invalid option\n", ft_strlen(": invalid option\n"));
	write(STDERR_FILENO, "cd: usage: cd [-L|-P] [dir]\n", \
		ft_strlen("cd: usage: cd [-L|-P] [dir]\n"));
	return (1);
}
