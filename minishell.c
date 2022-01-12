/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:59:52 by abridger          #+#    #+#             */
/*   Updated: 2022/01/12 17:46:34 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	memset(&data, 0, sizeof(t_data));
	ft_malloc_data(&data); // rewrite
	parse_envrmnt(&data, envp);
	// ft_test_readline(); // test
	ft_print_lsts(&data); // test
	ft_data_clear(&data);
	return (0);
}
