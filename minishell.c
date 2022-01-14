/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:59:52 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 16:40:00 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	data = NULL;
	if (argc != 1)
		return (put_err_message("Run program without arguments!"));
	else
	{
		action(data, envp);
	}
	return (0);
}
