/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:03:08 by abridger          #+#    #+#             */
/*   Updated: 2022/01/12 16:04:56 by abridger         ###   ########.fr       */
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
	t_env	**lst;
	t_env	*tmp;
	t_env	*curr;
	int		i;

	tmp = NULL;
	curr = NULL;
	i = 0;
	lst = data->envrmnt;
	if (*lst)
		curr = *lst;
	while (curr)
	{
		tmp = curr;
		printf("Line[%d]: %s\n", i, tmp->line);
		printf("Key[%d]: %s\n", i, tmp->key);
		printf("Value[%d]: %s\n", i, tmp->value);
		curr = curr->next;
		i++;
	}
}
