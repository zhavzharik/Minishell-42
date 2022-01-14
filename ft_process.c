/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:09:03 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 23:38:03 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_array_path(char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (str == NULL && envp[i] != NULL)
	{
		str = ft_strnstr(envp[i], "PATH", 4);
		i++;
	}
	return (ft_split(str, ':'));
}

int	create_fork(t_data *data, char **envp, char *str_path)
{
	data->pid = fork();
	if (data->pid == -1)
		return (ft_error(3, data, "Fork error"));
	else if (data->pid == 0)
	{
		if (execve(str_path, data->shell_cmd->cmd_args, envp) == -1)
			return (ft_error(3, data, "Error execution"));
	}
	return (0);
}

int	ft_exec_in_child(t_data *data, char **envp)
{
	char	*str_path;
	int		i;
	char	*tmp;
	int		check;

	i = 0;
	check = 0;
	while (data->array_path[i] != NULL && check != 1)
	{
		str_path = ft_strjoin(data->array_path[i], "/");
		tmp = str_path;
		str_path = ft_strjoin(tmp, data->shell_cmd->cmd_args[0]);
		free(tmp);
		if (access(str_path, 0) == 0)
			check = 1;
		i++;
	}
	if (check == 0)
		return (ft_error(2, data, "Command not found"));
	return (create_fork(data, envp, str_path));
}

int	ft_read_exec(t_data *data, char **envp)
{
	int		status;
	char	*input;
	int		i;

	i = 0;
	data->array_path = create_array_path(envp);
	data->shell_cmd = (t_cmd *)malloc(sizeof(t_cmd)); // test
	if (!data->shell_cmd) // test
		return (ft_error(1, data, "Malloc: ")); // test
	while (i < 5) // change EOF
	{
		input = readline("Minishell$ : ");
		add_history(input);
		data->shell_cmd->cmd_args = ft_split(input, ' '); // test
		data->shell_cmd->next = NULL; // test
		++i;
		if (input)
			free(input);
		ft_exec_in_child(data, envp);
		waitpid(-1, &status, 0);
	}
	return (0);
}
