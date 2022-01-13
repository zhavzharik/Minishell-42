/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/01/13 21:40:31 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	action(t_data *data, char **envp)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_error(1, NULL, "Malloc: "));
	else
	{
		ft_init_data(data, envp);
		// ft_test_readline(); // test
		ft_print_lsts(data); // test
		ft_data_clear(data);
	}
	return (0);
}
