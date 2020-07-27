/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_unknown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:04:17 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 23:38:15 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char **env)
{
	char *par;

	par = get_line_env(env, "PATH=");
	return (par+6);
}



int start_unknown_cmd(char *line, char **env)
{
	pid_t pid;
	char **param;
	char **paths;
	char *filename;
	char *fullfilename = "";

	param = ft_split((line+(skip_whitespace(line))), ' ');
	paths = ft_split(get_path(env), ':');
	pid = fork();

	if (pid == 0)
	{
		if (execve(param[0], param, env) == -1)
		{
		fullfilename = ft_strdup(*paths);
		fullfilename = ft_strjoin(fullfilename, "/");
		fullfilename = ft_strjoin(fullfilename, param[0]);
		while (*paths && execve(fullfilename, param, env) == -1)
		{
			paths++;
			fullfilename = ft_strdup(*paths);
		fullfilename = ft_strjoin(fullfilename, "/");
		fullfilename = ft_strjoin(fullfilename, param[0]);
		}
		}
	}
	else
		wait(&pid);
	return (0);
}
