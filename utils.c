/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:30:44 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 22:21:59 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line_env(char **env, char *param)
{
	while (*env)
	{
	//	printf("%s\n", *env);
		if (start_with_nospace(*env, param))
			return (*env);
		env++;
	}
	return NULL;
}

int ft_putstr(char *s)
{
	if (s != NULL)
		return write(1, s, ft_strlen(s));
	return (0);
}

int skip_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int skip_non_printale(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int start_with_nospace(char *str, char *con)
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return(0);
		i++;
	}
	return (1);
}

int start_with(char *str, char *con)
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return(0);
		i++;
	}
	if (!con[i] && (!str[i] || str[i] == ' '))
		return (1);
	return (0);
}

int count_cmd(char *line)
{
	int i;
	int count;

	if (!line)
		return (0);
	i = 0;
	count = 1;
	while(line[i])
	{
		if (line[i] == ';')
			count++;
		i++;
	}
	return (count);
}

char *ft_strcdup(char *str, char c)
{
	char			*dest;
	char			*temp;

	temp = (char *)malloc(sizeof(*dest) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str && *str != c)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}


int set_param(t_cmd **cmd, char *str, int cmd_id)
{
	(*cmd)->cmd = cmd_id;
	(*cmd)->str = ft_strcdup(str, ';');
	//printf("%d: %s\n", (*cmd)->cmd, (*cmd)->str);
	return(ft_strlen((*cmd)->str));
}

t_cmd **parse_cmd(char *line)
{
	int i;
	int cmd_i;
	t_cmd **cmds;

	cmds = malloc(sizeof(t_cmd**) * (count_cmd(line) + 1));
	cmds[0] = malloc(sizeof(t_cmd));
	i = 0;
	cmd_i = 0;
	while (line[i])
	{
		i += skip_non_printale(line + i);
		if (start_with(line+i, "echo"))
			i += set_param(&cmds[cmd_i], line + i + 4, ECHO) + 4;
		else if (start_with(line+i, "cd"))
			i += set_param(&cmds[cmd_i], line + i + 2, CD)+ 2;
		else if (start_with(line+i, "pwd"))
			i += set_param(&cmds[cmd_i], line + i + 3, PWD)+ 3;
		else if (start_with(line+i, "export"))
			i += set_param(&cmds[cmd_i], line + i + 6, EXPORT)+ 6;
		else if (start_with(line+i, "unset"))
			i += set_param(&cmds[cmd_i], line + i + 5, UNSET) + 5;
		else if (start_with(line+i, "env"))
			i += set_param(&cmds[cmd_i], line + i + 3, ENV) + 3;
		else if (start_with(line+i, "exit"))
			i += set_param(&cmds[cmd_i], line + i + 4, EXIT) + 4;
		else
			i += set_param(&cmds[cmd_i], line + i, UNKNOWN);
		cmd_i++;
		i++;
		cmds[cmd_i] = malloc(sizeof(t_cmd));
	}
	cmds[cmd_i]->cmd = END;
	return cmds;
}
