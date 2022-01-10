/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:45:00 by abridger          #+#    #+#             */
/*   Updated: 2022/01/10 18:12:50 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <string.h>

typedef struct s_env
{
	char			*line;
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_env	*ft_lstnew(const char *line);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_len_key(char *str);
int		ft_len_value(char *str);
int		parse_envrmnt(t_env **lst, char **envp);
void	ft_lst_clear(t_env **lst);
void	ft_test_readline(void); // delete
void	ft_print_lsts(t_env **lst); // delete

#endif
