/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:46:58 by abridger          #+#    #+#             */
/*   Updated: 2022/02/16 14:39:44 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_err_unset(t_shell *data, char *str)
{
	int		i;
	char	*part_str;
	char	*err;

	i = 0;
	part_str = NULL;
	err = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == 61)
		{
			data->exit_status = 1;
			part_str = ft_strjoin2("unset: `", str);
			err = ft_strjoin2(part_str, "': not a valid identifier");
			ft_str_clear(&part_str);
			write(STDERR_FILENO, err, ft_strlen(err));
			write(STDERR_FILENO, "\n", 1);
			ft_str_clear(&err);
			return (127);
		}
		i++;
	}
	data->exit_status = 0;
	return (0);
}

void	ft_del_lst_support(t_env *env, t_shell *data)
{
	t_env	*prev;
	t_env	*next;

	prev = NULL;
	next = NULL;
	prev = env->prev;
	next = env->next;
	if (env->prev && env->next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!env->prev && env->next)
	{
		data->env = next;
		next->prev = NULL;
	}
	else if (env->prev && !env->next)
		prev->next = NULL;
	else if (!env->prev && !env->next)
		data->env = NULL;
	ft_str_clear(&env->key);
	ft_str_clear(&env->sep);
	ft_str_clear(&env->value);
	free(env);
}

void	ft_del_lst(char *str, t_env *env, t_shell *data)
{
	while (env)
	{
		if (!ft_strcmp2(env->key, str))
		{
			ft_del_lst_support(env, data);
			break ;
		}
		else
			env = env->next;
	}
}

int	ft_exec_unset(t_shell *data, t_info *curr)
{
	int		i;
	int		height;
	t_env	*tmp;

	i = 1;
	height = ft_height_array(curr->argv);
	if (curr->nb_cmd == 4 && height > 0)
	{
		while (curr->argv[i])
		{
			if (!ft_strcmp2(curr->argv[i], "PATH"))
				data->flag_path = 1;
			tmp = data->env;
			if (!ft_err_unset(data, curr->argv[i]))
				ft_del_lst(curr->argv[i], tmp, data);
			i++;
		}
	}
	return (0);
}
