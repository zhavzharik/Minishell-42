/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:45:00 by abridger          #+#    #+#             */
/*   Updated: 2022/01/12 16:33:42 by abridger         ###   ########.fr       */
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
# include <sys/errno.h>
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

typedef struct s_cmd
{
	char			*command;
	int				nb_cmd;
	char			**args;
	int				red_flag;
	int				pipe_flag;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_data
{
	t_env			**envrmnt;
	t_cmd			*shell_cmd;
	int				pid;
	int				fd[2];
}					t_data;

int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_env	*ft_lstnew(const char *line);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_len_key(char *str);
int		ft_len_value(char *str);
int		parse_envrmnt(t_data *data, char **envp);
void	ft_lst_clear(t_env **lst);
int		ft_malloc_data(t_data *data);
void	ft_data_clear(t_data *data);
int		ft_error(int errnum, t_data *data, char *str);

void	ft_test_readline(void); // delete
void	ft_print_lsts(t_data *data); // delete

#endif
