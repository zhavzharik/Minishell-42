/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/16 14:51:28 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_env2(t_shell *msh, char *tmp)
{
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		tmp = NULL;
	}
	free(msh->str);
	msh->str = tmp;
}

static void	free_all4(t_shell *msh)
{
	if (msh->info->output_file)
		free(msh->info->output_file);
	if (msh->info->input_file)
		free(msh->info->input_file);
	if (msh->info->heredoc)
		free(msh->info->heredoc);
}

static void	free_all3(t_shell *msh)
{
	if (msh->str)
		free(msh->str);
	msh->have_a_pipe = 0;
	msh->check = 0;
}

static void	free_all2(t_shell *msh)
{
	t_env	*tmp2;

	tmp2 = msh->env;
	while (tmp2)
	{
		tmp2->is_sorted = 0;
		tmp2->next_sorted = NULL;
		tmp2->first = NULL;
		tmp2 = tmp2->next;
	}
}

void	free_all(t_shell *msh)
{
	t_info	*tmp;
	int		i;

	free_all2(msh);
	if (msh->info != NULL)
		msh->info = msh->info->head;
	while (msh->info)
	{
		i = 0;
		while (msh->info->argv && msh->info->argv[i])
			free(msh->info->argv[i++]);
		free(msh->info->argv);
		free_all4(msh);
		tmp = msh->info;
		msh->info = msh->info->next;
		free(tmp);
	}
	while (msh->array && msh->array[i])
		free(msh->array[i++]);
	free_all3(msh);
}
