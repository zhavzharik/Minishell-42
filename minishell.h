/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:45:00 by abridger          #+#    #+#             */
/*   Updated: 2022/01/14 23:37:32 by abridger         ###   ########.fr       */
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
	char			*line; // вся строка переменной окружения
	char			*key; // ключ переменной окружения (до "равно")
	char			*value; // значение переменной окружения (после "равно")
	struct s_env	*next;
}					t_env;

typedef struct s_cmd // куда сохранять имя файла, если подается? в одном листе данные для выполнения одной команды?
{
	char			**cmd_args; // распарсенная строка из ридлайн (до точки с запятой, т.е. одна команда с аргументами), cmd_args[0] - команда?
	int				nb_cmd; // номер команды, если подана команда, на которую надо написать свою функцию, если nb=8, например, то команда исполяется execve
	int				red_flag; // если есть редирект, подумать над флагами
	int				pipe_flag; // если есть пайп, подумать над флагами
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_data
{
	t_env			*envrmnt; // указатель на листы с переменными окружения
	t_cmd			*shell_cmd; // указатель на листы с командами и аргументами
	char			**array_path; // PATH значения, для исполнения execve
	int				pid; // для форка, чтобы в дочернем процессе запустить execve
	int				fd[2]; // дескрипторы для редиректа, может нужно переместить их в листы с командами?
}					t_data;

int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);

t_env	*ft_lstnew(const char *line);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_len_key(char *str);
int		ft_len_value(char *str);
t_env	*parse_envrmnt(t_env *lst, char **envp);
void	ft_lst_clear(t_env **lst);

int		ft_init_data(t_data *data, char **envp);
void	ft_data_clear(t_data *data); // переписать, не работает
int		ft_error(int errnum, t_data *data, char *str); // переписать c errno
int		put_err_message(char *str);
int		action(t_data *data, char **envp);
char	**create_array_path(char **envp);
int		create_fork(t_data *data, char **envp, char *str_path);
int		ft_exec_in_child(t_data *data, char **envp);
int		ft_read_exec(t_data *data, char **envp);

void	ft_test_readline(void); // delete
void	ft_print_lsts(t_data *data); // delete для проверки печати переменных окружения из листов

#endif
