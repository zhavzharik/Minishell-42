/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/02/16 14:17:31 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_err_no_dir(t_shell *data, char *str)
{
	data->exit_status = 127;
	write(STDERR_FILENO, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
	return (1);
}

void	ft_get_home(t_shell *data)
{
	t_env	*tmp;
	int		check;

	tmp = data->env;
	check = 0;
	while (tmp && check == 0)
	{
		if (0 == ft_strcmp2(tmp->key, "HOME"))
		{
			data->home_value = ft_strdup(tmp->value);
			check = 1;
		}
		tmp = tmp->next;
	}
}

int	ft_add_home_dir(t_shell *data, char *line, char *curr_pwd)
{
	char	*end_dir;
	char	*dir;

	if (line)
	{
		end_dir = ft_substr(line, 1, ft_strlen(line) - 1);
		dir = ft_strjoin2(data->home_value, end_dir);
		free(end_dir);
	}
	else
		dir = data->home_value;
	chdir(dir);
	ft_change_pwd_env(data, curr_pwd, dir);
	free(dir);
	return (0);
}

int	ft_check_args(t_shell *data, t_info *curr, char *curr_pwd)
{
	if (ft_height_array(curr->argv) == 1)
		return (ft_add_home_dir(data, NULL, curr_pwd));
	else if (curr->argv && ft_height_array(curr->argv) > 2)
		return (ft_err_many_args(data));
	else if (!ft_strncmp(curr->argv[1], "-", 1) && ft_strlen(curr->argv[1]) > 1)
		return (ft_err_option(data, curr->argv[1]));
	else if (!ft_strcmp(curr->argv[1], "-"))
		return (ft_print_dir(data, curr_pwd));
	else if (!ft_strncmp(curr->argv[1], "~", 1))
		return (ft_add_home_dir(data, curr->argv[1], curr_pwd));
	else if (curr->argv[1] && chdir(curr->argv[1]) < 0)
		return (ft_err_no_dir(data, curr->argv[1]));
	return (0);
}
