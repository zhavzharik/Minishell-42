/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/14 17:53:43 by pkari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_quotes(t_shell *msh, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = *i;
	while (msh->str[++(*i)])
		if (msh->str[*i] == '\'')
			break ;
	if (msh->str[*i] == 0)
		return (syntax_error(msh, msh->str + *i, 1));
	tmp = ft_substr(msh->str, 0, j);
	tmp1 = ft_substr(msh->str, j + 1, *i - j - 1);
	tmp2 = ft_strdup(msh->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp1);
	tmp = ft_strjoin(tmp, tmp2);
	free(msh->str);
	*i -= 2;
	msh->str = tmp;
	return (0);
}

int	double_quotes(t_shell *msh, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = *i;
	while (msh->str[++(*i)])
	{
		if (msh->str[*i] == '\"')
			break ;
		else if ((msh->str[*i] == '$') && (msh->str[*i + 1] != '\"'))
			dollar(msh, i);
	}
	if (msh->str[*i] == 0)
		return (syntax_error(msh, msh->str + *i, 1));
	tmp = ft_substr(msh->str, 0, j);
	tmp1 = ft_substr(msh->str, j + 1, *i - j - 1);
	tmp2 = ft_strdup(msh->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp1);
	tmp = ft_strjoin(tmp, tmp2);
	free(msh->str);
	*i -= 2;
	msh->str = tmp;
	return (0);
}
