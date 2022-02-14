/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:04:25 by abridger          #+#    #+#             */
/*   Updated: 2022/01/29 23:21:47 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_find_first(t_shell *data)
{
	t_env	*tmp_min;
	t_env	*tmp_next;
	t_env	*env;
	int		diff;
	int		check;

	env = data->env;
	tmp_min = env;
	tmp_next = env->next;
	check = 0;
	while (env)
	{
		diff = ft_strcmp2(tmp_min->key, tmp_next->key);
		if (diff > 0)
			tmp_min = tmp_next;
		if (check == 0)
			env = env->next->next;
		check = 1;
		if (check == 1)
			env = env->next;
		tmp_next = env;
	}
	return (tmp_min);
}

int	ft_unsorted(t_shell *data)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = data->env;
	while (curr)
	{
		if (curr->is_sorted == 0)
			count++;
		curr = curr->next;
	}
	return (count);
}

t_env	*ft_find_next(t_shell *data)
{
	t_env	*tmp_min;
	t_env	*tmp_next;
	t_env	*env;
	int		diff;

	env = data->env;
	data->check = 0;
	while (env)
	{
		if (env->is_sorted == 0 && data->check == 0)
		{
			tmp_min = env;
			env = env->next;
			data->check = 1;
		}
		if (env->is_sorted == 0 && data->check == 1)
		{
			tmp_next = env;
			diff = ft_strcmp2(tmp_min->key, tmp_next->key);
			if (diff > 0)
				tmp_min = tmp_next;
		}
		env = env->next;
	}
	return (tmp_min);
}

t_env	*ft_find_last(t_shell *data)
{
	t_env	*tmp_last;
	t_env	*env;
	int		check;

	env = data->env;
	check = 0;
	while (env && check == 0)
	{
		if (env->is_sorted == 0)
		{
			tmp_last = env;
			check = 1;
		}
		env = env->next;
	}
	return (tmp_last);
}

t_env	*ft_sort_env(t_shell *data)
{
	t_env	*min;
	t_env	*next_min;
	t_env	*curr;

	min = ft_find_first(data);
	min->first = min;
	min->is_sorted = 1;
	curr = min;
	next_min = NULL;
	while (ft_unsorted(data) > 1)
	{
		next_min = ft_find_next(data);
		curr->next_sorted = next_min;
		curr = next_min;
		next_min->is_sorted = 1;
	}
	if (ft_unsorted(data) == 1)
	{
		next_min = ft_find_last(data);
		curr->next_sorted = next_min;
		next_min->is_sorted = 1;
	}
	return (min);
}
