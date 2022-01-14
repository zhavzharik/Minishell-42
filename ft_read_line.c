/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:03:08 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 18:19:32 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test_readline(void)
{
	char	*input;
	int		size;
	int		i;
	char	cwd[100];

	i = 0;
	while (i < 5)
	{
		input = readline("Minishell$ : ");
		size = ft_strlen(input);
		if (!strcmp(input, "pwd"))
			printf("%s", getcwd(cwd, sizeof(cwd)));
		else
		{
			add_history(input);
			printf("%s", input);
			printf("\n");
			printf("%d", size);
		}
		printf("\n");
		++i;
		if (input)
			free(input);
	}
}

void	ft_print_lsts(t_data *data)
{
	if (data->envrmnt != NULL)
	{
		while (data->envrmnt)
		{
			printf("%s\n", data->envrmnt->line);
			data->envrmnt = data->envrmnt->next;
		}
	}
	else
		printf("test");
}
