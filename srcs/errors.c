/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/16 14:41:07 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(t_shell *msh, char *str, int len)
{
	if (str[0] == 0)
	{
		write(2, "minishell: syntax error near unexpected token `newline'", 55);
		write(2, "\n", 1);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, str, len);
		write(2, "'\n", 2);
	}
	msh->exit_status = 258;
	return (1);
}

void	errno_error(t_shell *msh)
{
	perror("minishell");
	msh->exit_status = 1;
	msh->info->error = 1;
	msh->info->token = 0;
}

void	execve_error(t_shell *data)
{
	struct stat	path;

	if ((!ft_strncmp(data->info->argv[0], "/", 1))
		|| (!ft_strncmp(data->info->argv[0], "./", 2))
		|| (!ft_strncmp(data->info->argv[0], "../", 3)))
	{
		write(2, "minishell: ", 11);
		perror(data->info->argv[0]);
		exit (127);
	}
	else if (!stat(data->info->argv[0], &path) && S_ISDIR(path.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, data->info->argv[0], (size_t)ft_strlen(data->info->argv[0]));
		write(2, ": is a directory\n", 17);
		exit (126);
	}
	write(2, "minishell: ", 11);
	write(2, data->info->argv[0], (size_t)ft_strlen(data->info->argv[0]));
	if (data->flag_path == 1)
		write(2, ": No such file or directory\n", 29);
	else
		write(2, ": command not found\n", 21);
	exit (127);
}
