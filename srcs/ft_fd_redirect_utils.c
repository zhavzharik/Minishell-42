/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:20:32 by abridger          #+#    #+#             */
/*   Updated: 2022/02/16 13:53:01 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_output(t_info *curr)
{
	if (curr->fd_output_file != -2)
	{
		dup2(curr->fd_output_file, 1);
	}
}

void	ft_redirect_input(t_info *curr)
{
	if (curr->fd_input_file != -2 && curr->redirect_flag == 1)
	{
		dup2(curr->fd_input_file, STDIN_FILENO);
	}
	if (curr->heredoc != NULL && curr->redirect_flag == 2)
	{
		dup2(curr->fd_heredoc_file, STDIN_FILENO);
	}
}

void	ft_read_input(t_info *curr)
{
	if (curr->redirect_flag == 1)
		dup2(curr->fd_input_file, 0);
	else if (curr->redirect_flag == 2)
		dup2(curr->fd_heredoc_file, 0);
	else if (curr->prev->redirect_flag == 1 || curr->prev->redirect_flag == 0)
		dup2(curr->prev->fd_input_file, 0);
	else if (curr->prev->redirect_flag == 2)
		dup2(curr->prev->fd_heredoc_file, 0);
}
