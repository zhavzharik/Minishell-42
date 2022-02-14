/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/02/14 22:45:59 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_err_no_dir(t_shell *data, char *str)
{
	data->exit_status = 1;
	write(STDERR_FILENO, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
	return (1);
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
	if (check == 1)
	{
		chdir(str);
		ft_change_pwd_env(data, curr_pwd, str);
	}
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str); // add if (check == 0)
	return (0);
}

char	*ft_get_home(t_shell *data)
{
	t_env	*tmp;
	int		check;
	char	*str;

	tmp = data->env;
	check = 0;
	while (tmp && check == 0)
	{
		if (0 == ft_strcmp2(tmp->key, "HOME"))
		{
			str = ft_strdup(tmp->value);
			check = 1;
		}
		tmp = tmp->next;
	}
	return (str);
}

int	ft_add_home_dir(t_shell *data, char *line, char *curr_pwd)
{
	char	*str;
	char	*end_dir;
	char	*dir;

	str = ft_get_home(data);
	if (line)
	{
		end_dir = ft_substr(line, 1, ft_strlen(line) - 1);
		dir = ft_strjoin2(str, end_dir);
		free(end_dir);
	}
	else
		dir = str;
	free(str);
	chdir(dir);
	ft_change_pwd_env(data, curr_pwd, dir);
	free(dir);
	return (0);
}
