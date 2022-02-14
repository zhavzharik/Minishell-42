/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:45:11 by abridger          #+#    #+#             */
/*   Updated: 2022/02/13 01:58:18 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env_clear(t_env **lst)
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
		ft_str_clear(&tmp->key);
		ft_str_clear(&tmp->sep);
		ft_str_clear(&tmp->value);
		curr = curr->next;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}

void	ft_data_clear(t_shell *data)
{
	if (data)
	{
		if (data->env != NULL)
			ft_env_clear(&data->env);
		free(data);
	}
	data = NULL;
}

void	ft_str_clear(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}
