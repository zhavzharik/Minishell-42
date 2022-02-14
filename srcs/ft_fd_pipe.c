/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:16:15 by abridger          #+#    #+#             */
/*   Updated: 2022/02/14 18:14:11 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe_init(t_shell *data, t_info *curr)
{
	if (curr->token == TOKEN_PIPE)
	{
		if (pipe(curr->fd_pipe) == -1)
			return (ft_error(data, ft_one_colon("pipe")));
	}
	return (0);
}

void	ft_pipe_close(t_shell *data, t_info *curr)
{
	if (data->count > 1 && curr->token == TOKEN_PIPE)
	{
		close(curr->fd_pipe[0]);
		close(curr->fd_pipe[1]);
	}
	if (data->count > 1 && curr->prev)
	{
		close(curr->prev->fd_input_file);
		close(curr->prev->fd_output_file);
	}
}

static void	ft_dup2_out(t_info *curr)
{
	if (!curr->output_file)
		dup2(curr->fd_pipe[1], 1);
	else
		dup2(curr->fd_output_file, 1);
}

void	ft_pipe_dup_child(t_shell *data, t_info *curr)
{
	if (data->count > 1 && !curr->prev)
	{
		curr->fd_pipe[0] = dup(data->save_in);
		ft_dup2_out(curr);
	}
	else if (data->count > 1 && curr->prev && curr->token != TOKEN_PIPE)
	{
		dup2(curr->prev->fd_input_file, 0);
		ft_redirect_output(curr);
		ft_close_curr_files(curr);
	}
	else if (data->count > 1 && curr->prev && curr->token == TOKEN_PIPE)
	{
		dup2(curr->prev->fd_input_file, 0);
		ft_dup2_out(curr);
	}
	ft_pipe_close(data, curr);
}

void	ft_pipe_dup_parent(t_shell *data, t_info *curr)
{
	if (data->count > 1 && curr->token == TOKEN_PIPE)
	{
		if (!curr->input_file)
			curr->fd_input_file = dup(curr->fd_pipe[0]);
	}
	else if (data->count > 1 && curr->prev && curr->token != TOKEN_PIPE)
	{
		ft_close_curr_files(curr);
		ft_close_saved_fd(data);
	}
	ft_pipe_close(data, curr);
}
