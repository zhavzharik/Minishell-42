/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:15:16 by abridger          #+#    #+#             */
/*   Updated: 2022/02/12 23:41:58 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_check(const char *line, t_env *tmp)
{
	int		len_key;
	char	*key;
	char	*sep;
	int		check;

	len_key = ft_len_key((char *)line);
	check = 0;
	key = ft_substr(line, 0, len_key);
	if (ft_strlen((char *)line) - len_key >= 1)
		sep = ft_substr(line, len_key, 1);
	else
		sep = NULL;
	while (tmp && check == 0)
	{
		if (!ft_strcmp2(key, tmp->key) && tmp->sep)
			check = 2;
		else if (!ft_strcmp2(key, tmp->key) && !tmp->sep)
			check = 1;
		tmp = tmp->next;
	}
	ft_str_clear(&key);
	ft_str_clear(&sep);
	return (check);
}

void	ft_lst_change_value(t_env *lst, const char *line)
{
	int		len_key;
	int		len_value;
	char	*key;
	int		done;

	done = 0;
	len_key = ft_len_key((char *)line);
	len_value = ft_len_value((char *)line);
	key = ft_substr(line, 0, len_key);
	while (lst && !done)
	{
		if (!ft_strcmp2(key, lst->key))
		{
			ft_str_clear(&lst->value);
			if (ft_strlen((char *)line) - len_key >= 1)
				lst->sep = ft_substr(line, len_key, 1);
			if (len_value > 0)
				lst->value = ft_substr(line, len_key + 1, len_value);
			else
				lst->value = NULL;
			done = 1;
		}
		lst = lst->next;
	}
	ft_str_clear(&key);
}

void	ft_add_variable(t_info *curr, t_shell *data)
{
	int		i;
	int		check;
	t_env	*new;
	t_env	*env;
	t_env	*tmp;

	i = 1;
	new = NULL;
	while (curr->argv[i])
	{
		tmp = data->env;
		env = data->env;
		check = ft_env_check(curr->argv[i], tmp);
		if (check == 0)
		{
			new = ft_lstnew(curr->argv[i]);
			ft_lstadd_back(&env, new);
		}
		else if (check == 1)
			ft_lst_change_value(env, curr->argv[i]);
		i++;
	}
}

void	ft_print_export(t_shell *data, int height)
{
	t_env	*sorted;

	sorted = NULL;
	if (data->env != NULL && height == 1)
	{
		sorted = ft_sort_env(data);
		while (sorted)
		{
			write(1, "declare -x ", ft_strlen("declare -x "));
			write(1, sorted->key, ft_strlen(sorted->key));
			if (sorted->sep)
			{
				write(1, sorted->sep, ft_strlen(sorted->sep));
				write(1, "\"", 1);
			}
			if (sorted->value)
				write(1, sorted->value, ft_strlen(sorted->value));
			if (sorted->sep)
				write(1, "\"", 1);
			write(1, "\n", 1);
			sorted = sorted->next_sorted;
		}
	}
}

int	ft_exec_export(t_shell *data, t_info *curr)
{
	int		height;

	height = ft_height_array(curr->argv);
	if (curr->nb_cmd == 3)
	{
		if (height > 1)
		{
			if (ft_check_key(curr->argv[1]) == 1)
				return (ft_err_export(data, curr->argv[1]));
			ft_add_variable(curr, data);
		}
		ft_print_export(data, height);
		data->exit_status = 0;
	}
	return (0);
}
