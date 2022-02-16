/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/16 14:25:36 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//**start new functions**//

static char	*ft_get_path(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(key, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

char	*get_prog_name(t_shell *data, t_info *curr)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*str;

	i = 0;
	str = curr->argv[0];
	path = ft_split(ft_get_path(data->env, "PATH"), ':');
	while (path[i])
	{
		tmp = ft_strjoin2("/", curr->argv[0]);
		tmp = ft_strjoin(path[i], tmp);
		if (access(tmp, 0) == 0)
			str = tmp;
		else
			free(tmp);
		i++;
	}
	free(path);
	return (str);
}

static int	ft_lstsize2(t_env *env)
{
	int	i;

	i = 1;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**get_arr_from_lst(t_shell *data)
{
	t_env	*tmp;
	int		i;
	char	*str;

	tmp = data->env;
	i = ft_lstsize2(tmp);
	data->array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp)
	{
		str = ft_strjoin2(tmp->key, "=");
		data->array[i] = ft_strjoin2(str, tmp->value);
		free(str);
		i++;
		tmp = tmp->next;
	}
	data->array[i] = NULL;
	return (data->array);
}

void	exit_status_handler(t_shell *data)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
	else
		data->exit_status = WEXITSTATUS(status);
}
