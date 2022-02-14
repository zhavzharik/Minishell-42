/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:12:43 by abridger          #+#    #+#             */
/*   Updated: 2022/02/14 22:46:20 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_oldpwd_env(t_shell *data, char *curr_pwd)
{
	t_env	*tmp;
	t_env	*new;
	char	*str;

	tmp = data->env;
	str = ft_strjoin2("OLDPWD=", curr_pwd);
	new = ft_lstnew(str);
	ft_lstadd_back(&tmp, new);
	ft_str_clear(&str);
}

void	ft_change_oldpwd_env(t_shell *data, char *curr_pwd, int check)
{
	t_env	*tmp;

	tmp = data->env;
	if (check == 1)
	{
		while (tmp)
		{
			if (0 == ft_strcmp2(tmp->key, "OLDPWD"))
			{
				free(tmp->value);
				tmp->value = ft_strdup(curr_pwd);
				check = 0;
			}
			tmp = tmp->next;
		}
		if (check == 1)
			ft_add_oldpwd_env(data, curr_pwd);
	}
}

void	ft_change_pwd_env(t_shell *data, char *curr_pwd, char *new_pwd)
{
	t_env	*tmp;
	int		check;

	tmp = data->env;
	check = 0;
	while (tmp && check == 0)
	{
		if (0 == ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_pwd);
			check = 1;
		}
		tmp = tmp->next;
	}
	if (check == 1)
		ft_change_oldpwd_env(data, curr_pwd, check);
}

int	ft_err_many_args(t_shell *data)
{
	data->exit_status = 1;
	write(STDERR_FILENO, "minishell: cd: too many arguments\n", \
		ft_strlen("minishell: cd: too many arguments\n"));
	return (1);
}

int	ft_exec_cd(t_shell *data, t_info *curr)
{
	char	buf1[1024];
	char	buf2[1024];
	char	*curr_pwd;
	char	*new_pwd;

	if (curr->nb_cmd == 1)
	{
		curr_pwd = getcwd(buf1, sizeof(buf1));
		if (ft_height_array(curr->argv) == 1)
			return (ft_add_home_dir(data, NULL, curr_pwd));
		if (curr->argv && ft_height_array(curr->argv) > 2)
			return (ft_err_many_args(data));
		if (!ft_strcmp(curr->argv[1], "-"))
			return (ft_print_dir(data, curr_pwd));
		if (!ft_strncmp(curr->argv[1], "~", 1))
			return (ft_add_home_dir(data, curr->argv[1], curr_pwd));
		if (curr->argv[1] && chdir(curr->argv[1]) < 0)
			return (ft_err_no_dir(data, curr->argv[1]));
		if (curr->argv[1] && curr->token == TOKEN_PIPE)
			chdir(curr_pwd);
		new_pwd = getcwd(buf2, sizeof(buf2));
		ft_change_pwd_env(data, curr_pwd, new_pwd);
	}
	return (0);
}
