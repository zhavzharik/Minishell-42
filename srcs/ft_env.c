/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:31:17 by abridger          #+#    #+#             */
/*   Updated: 2022/02/12 23:34:23 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wrong_path(t_shell *data)
{
	t_env	*curr;

	curr = data->env;
	while (curr)
	{
		if (!ft_strcmp2(curr->key, "PATH"))
			return (0);
		curr = curr->next;
	}
	data->exit_status = 127;
	write(STDERR_FILENO, "minishell: env: No such file or directory\n", \
		ft_strlen("minishell: env: No such file or directory\n"));
	return (1);
}

int	ft_err_env_args(t_shell *data, char *str)
{
	data->exit_status = 127;
	write(STDERR_FILENO, "env: \'", ft_strlen("env: \'"));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\': No such file or directory\n", \
		ft_strlen("\': No such file or directory\n"));
	return (1);
}

int	ft_exec_env(t_shell *data, t_info *curr)
{
	t_env *tmp;

	tmp = data->env;
	data->exit_status = 0;
	if (curr->nb_cmd == 6 && !curr->argv[1])
	{
		if (data->env != NULL && !ft_wrong_path(data))
		{
			while (tmp)
			{
				if (tmp->sep)
				{
					write(1, tmp->key, ft_strlen(tmp->key));
					write(1, tmp->sep, ft_strlen(tmp->sep));
					if (tmp->value)
						write(1, tmp->value, ft_strlen(tmp->value));
					write(1, "\n", 1);
				}
				tmp = tmp->next;
			}
		}
	}
	else if (curr->nb_cmd == 6 && curr->argv[1] && !ft_wrong_path(data))
		return (ft_err_env_args(data, curr->argv[1]));
	return (0);
}
