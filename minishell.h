/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:08:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:17:42 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 30

# define UNKNOWN 0
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define END 8


# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdio.h>
#include <limits.h>

# define FDS 14000

typedef struct s_cmd
{
	int cmd;
	char *str;
} t_cmd;

int ft_putstr(char *s);
t_cmd **parse_cmd(char *line);
char		*ft_itoa(int n);
char *ft_strcdup(char *str, char c);
int skip_non_printale(char *str);
int start_with(char *str, char *con);
int skip_whitespace(char *str);
char *get_cur_path();
int start_pwd(char *line);
int start_echo(char *line);
int start_unknown_cmd(char *line);
int start_cd(char *line);
int start_export(char *line);
int start_unset(char *line);
int start_env(char *line, char **envp);

/*
* GET NEXT LINE
*/

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_find_lbreak(char *s);
void			free_chr(char **chr);
char			*ft_strdup(char *str);
char			*ft_strjoin(char *s1, char *s2);
#endif

