/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_unknown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:04:17 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/28 17:17:13 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char **env)
{
	char *par;

	par = get_line_env(env, "PATH=");
	return (par+6);
}

int file_exists (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}

void start_exec(char *cmd, char **param, char **env)
{
	pid_t pid;
	//pid_t pid2;
	int fd[2];

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
    	close(fd[0]);
    	close(fd[1]);
		execve(cmd, param, env);
		exit(1);
	} else {

		pid = fork();
		if(pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execve(cmd, param, env);
			exit(1);
		}
		else
		{
			int status;
			close(fd[0]);
			close(fd[1]);
			wait(&pid);
			//waitpid(pid, &status, 0);


		}
	}


}

void show_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

int start_unknown_cmd(char *line, char **env)
{

	char **param1;
	char **param2;
	char **paths;
	char *fullfilename = "";
	int is_exist;
	char **comands;
	int i;

	comands = ft_split((line+(skip_whitespace(line))), '|');
	param2 = ft_split(comands[0], ' ');
	param2 = ft_split(comands[1], ' ');
	paths = ft_split(get_path(env), ':');
	is_exist = 0;
	fullfilename = param1[0];
	i = 0;
	while (paths[i])
	{
		if (file_exists(fullfilename))
		{
			is_exist = 1;
			break ;
		}
		fullfilename = ft_strdup(paths[i]);
		fullfilename = ft_strjoin(fullfilename, "/");
		fullfilename = ft_strjoin(fullfilename, param1[0]);
		i++;
	}
	if (!is_exist)
	{
		printf("minishell: No such file or directory: %s\n", param1[0]);
	} else {
		start_exec(fullfilename, param1, env);
	}

	free(fullfilename);
	fullfilename = param2[0];
	i = 0;
	is_exist = 0;
	while (paths[i])
	{
		if (file_exists(fullfilename))
		{
			is_exist = 1;
			break ;
		}
		fullfilename = ft_strdup(paths[i]);
		fullfilename = ft_strjoin(fullfilename, "/");
		fullfilename = ft_strjoin(fullfilename, param2[0]);
		i++;
	}
	if (!is_exist)
	{
		printf("minishell: No such file or directory: %s\n", param2[0]);
	} else {
		start_exec(fullfilename, param2, env);
	}





	return(0);
}

int start_unknown_cmd2(char *line, char **env)
{
	pid_t pid;
	char **param1;
	char **param2;
	char **paths;
	char *filename;
	char *fullfilename = "";
	char **comands;

	int is_ok;
	comands = ft_split((line+(skip_whitespace(line))), '|');

	param1 = ft_split(comands[0], ' ');
	if (comands[1])
		param2 = ft_split(comands[1], ' ');
	is_ok = 0;
	paths = ft_split(get_path(env), ':');
	pid = fork();
	if (pid == 0)
	{
		is_ok = 0;
		if (execve(param1[0], param1, env) == -1)
		{
			fullfilename = ft_strdup(*paths);
			fullfilename = ft_strjoin(fullfilename, "/");
			fullfilename = ft_strjoin(fullfilename, param1[0]);
			while (*paths)
			{
				execve(fullfilename, param1, env);
				if (errno == -1)
					printf(":command not found %d\n", errno);
				paths++;
				fullfilename = ft_strdup(*paths);
				fullfilename = ft_strjoin(fullfilename, "/");
				fullfilename = ft_strjoin(fullfilename, param1[0]);
			}
			kill(pid, 0);
			printf(":command not found %d\n", errno);
		}



	} else if (pid < 0){
		printf("pid < 0 %s \n", param1[0]);
	} else
		wait(&pid);
	return (0);
}
