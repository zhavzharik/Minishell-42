/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:59:52 by abridger          #+#    #+#             */
/*   Updated: 2022/01/10 18:28:12 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envrmnt;

	(void) argc;
	(void) argv;
	envrmnt = NULL;
	parse_envrmnt(&envrmnt, envp);
	ft_test_readline();
	// ft_print_lsts(&envrmnt);
	if (envrmnt)
		ft_lst_clear(&envrmnt);
	return (0);
}
