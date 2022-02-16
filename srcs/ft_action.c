/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/02/16 13:50:36 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	action(t_shell *data)
{
	ft_define_cmd(data);
	ft_execution_cycle(data);
	signal(SIGINT, ctrl_c);
	return (0);
}

void	ft_define_cmd(t_shell *data)
{
	t_info	*curr;

	curr = NULL;
	if (data->info)
		curr = data->info->head;
	while (curr)
	{
		if (curr->argv && !ft_strcmp2(curr->argv[0], "echo"))
			curr->nb_cmd = 0;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "cd"))
			curr->nb_cmd = 1;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "pwd"))
			curr->nb_cmd = 2;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "export"))
			curr->nb_cmd = 3;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "unset"))
			curr->nb_cmd = 4;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "exit"))
			curr->nb_cmd = 5;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "env"))
			curr->nb_cmd = 6;
		else if (curr->argv)
			curr->nb_cmd = 7;
		curr = curr->next;
	}
}

int	ft_simple_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	if (data->count == 1)
	{
		ft_redirect_dup(curr);
		if (curr->nb_cmd >= 0 && curr->nb_cmd < 7)
			(func)[curr->nb_cmd](data, curr);
		else
		{
			curr->pid = fork();
			if (curr->pid == -1)
				return (ft_error(data, ft_one_colon("fork")));
			else if (curr->pid == 0)
			{
				if (execve(get_prog_name(data, curr), data->info->argv,
						get_arr_from_lst(data)) == -1)
					execve_error(data);
				exit(data->exit_status);
			}
			exit_status_handler(data);
		}
		ft_close_saved_fd(data);
	}
	return (0);
}

int	ft_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	if (data->count > 1)
	{
		curr->pid = fork();
		if (curr->pid == -1)
			return (ft_error(data, ft_one_colon("fork")));
		else if (curr->pid == 0)
		{
			ft_pipe_dup_child(data, curr);
			if (curr->nb_cmd < 7 && curr->nb_cmd >= 0)
				(func)[curr->nb_cmd](data, curr);
			else
			{
				if (execve(get_prog_name(data, curr), curr->argv,
						get_arr_from_lst(data)) == -1)
					execve_error(data);
			}
			exit(data->exit_status);
		}
		exit_status_handler(data);
		ft_pipe_dup_parent(data, curr);
	}
	return (0);
}

void	ft_execution_cycle(t_shell *data)
{
	t_info		*curr;
	t_builtin	*func;

	curr = data->info->head;
	data->count = msh_lstsize(curr);
	func = create_array_function();
	ft_init_saved_fd(data);
	while (curr)
	{
		signal(SIGINT, ctrl_c2);
		ft_pipe_init(data, curr);
		ft_simple_execute(data, curr, func);
		ft_execute(data, curr, func);
		curr = curr->next;
	}
	free(func);
}
