#include "../includes/minishell.h"

int dollar_question(t_shell *msh, int *i, int j)
{
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp = ft_substr(msh->str, 0, j);
	tmp1 = ft_itoa(msh->exit_status);
	j = ft_strlen(tmp1);
	tmp2 = ft_strdup(msh->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp1);
	tmp = ft_strjoin(tmp, tmp2);
	free(msh->str);
	msh->str = tmp;
	*i += j - 2;
	return (0);
}

int dollar_ignore(t_shell *msh, int *i, int j)
{
	char *tmp;
	char *tmp1;

	tmp = ft_substr(msh->str, 0, j);
	tmp1 = ft_strdup(msh->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp1);
	free(msh->str);
	msh->str = tmp;
	*i -= 2;
	return (0);
}

int dollar_pass(t_shell *msh, int *i, int j)
{
	char *tmp;
	char *tmp1;

	while (msh->str[*i] == ' ' || msh->str[*i] == '\t')
		(*i)++;
	tmp = ft_substr(msh->str, 0, j + 2);
	tmp1 = ft_strdup(msh->str + *i);
	tmp = ft_strjoin(tmp, tmp1);
	free(msh->str);
	msh->str = tmp;
	*i = *i - j + 2;
	return (0);
}

int dollar_env(t_shell *msh, int *i, int j)
{
	char *tmp;
	char *tmp1;
	char *tmp2;
	char *dollar_env;

	while (ft_isalnum(msh->str[*i]) || msh->str[*i] == '_')
		(*i)++;
	tmp = ft_substr(msh->str, 0, j);
	tmp1 = ft_substr(msh->str, j + 1, *i - j - 1);
	dollar_env = get_dollar_env(msh->env, tmp1);
	tmp2 = ft_strdup(msh->str + *i);
	*i = *i + ft_strlen(dollar_env) - ft_strlen(tmp1) - 2;
	free(tmp1);
	tmp1 = ft_strjoin2(dollar_env, tmp2);
	free(tmp2);
	tmp = ft_strjoin2(tmp, tmp1);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		tmp = NULL;
	}
	free(msh->str);
	msh->str = tmp;
	return (0);
}

int dollar(t_shell *msh, int *i)
{
	int j;

	j = *i;
	(*i)++;
	if (msh->str[*i] == '?')
		return (dollar_question(msh, i, j));
	else if (msh->str[*i] == ' ' || msh->str[*i] == '\t')
		return (dollar_pass(msh, i, j));
	else if (msh->str[*i] == '\'' || msh->str[*i] == '\"' || ft_isdigit(msh->str[*i]))
		return (dollar_ignore(msh, i, j));
	else
		return (dollar_env(msh, i, j));
	return (0);
}

