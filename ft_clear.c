/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:45:11 by abridger          #+#    #+#             */
/*   Updated: 2022/01/12 15:30:38 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strs_free(t_env *lst)
{
	if (lst)
	{
		if (lst->line)
			free(lst->line);
		lst->line = NULL;
		if (lst->key)
			free(lst->key);
		lst->key = NULL;
		if (lst->value)
			free(lst->value);
		lst->value = NULL;
	}
}

void	ft_lst_clear(t_env **lst)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = NULL;
	curr = NULL;
	if (*lst)
		curr = *lst;
	while (curr)
	{
		tmp = curr;
		ft_strs_free(tmp);
		curr = curr->next;
		free(tmp);
	}
	*lst = NULL;
}

void	ft_data_clear(t_data *data)
{
	if (data)
	{
		ft_lst_clear(data->envrmnt);
		free(data);
	}
	data = NULL;
}
