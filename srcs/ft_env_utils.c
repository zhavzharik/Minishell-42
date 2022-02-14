/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:46:39 by abridger          #+#    #+#             */
/*   Updated: 2022/01/28 22:26:14 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_ptr(t_env **new)
{
	(*new)->first = NULL;
	(*new)->next_sorted = NULL;
	(*new)->is_sorted = 0;
}

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
		new->key = ft_substr(line, 0, len_key);
		if (ft_strlen((char *)line) - len_key >= 1)
			new->sep = ft_substr(line, len_key, 1);
		else
			new->sep = NULL;
		if (len_value > 0)
			new->value = ft_substr(line, len_key + 1, len_value);
		else
			new->value = NULL;
		new->prev = NULL;
		new->next = NULL;
		ft_add_ptr(&new);
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
	t_env	*last;

	last = NULL;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	last->next->prev = last;
}

t_env	*parse_envrmnt(t_env *lst, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(envp[i]);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}
