/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:46:39 by abridger          #+#    #+#             */
/*   Updated: 2022/01/13 20:48:24 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(const char *line)
{
	t_env	*new;
	int		len_key;
	int		len_value;

	len_key = ft_len_key((char *)line);
	len_value = ft_len_value((char *)line);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->line = ft_strdup(line);
		new->key = ft_substr(line, 0, len_key);
		if (len_value > 0)
			new->value = ft_substr(line, len_key + 1, len_value);
		else
			new->value = NULL;
		new->next = NULL;
	}
	return (new);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

t_env	*parse_envrmnt(t_env *lst, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	// (void) data;
	// data->envrmnt = NULL;
	// lst = data->envrmnt;
	// lst = NULL;
	while (envp[i]) // errors?
	{
		tmp = ft_lstnew(envp[i]);
		// printf("%s\n", tmp->line); // delete
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}
