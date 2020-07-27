/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:20:34 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char *read_line()
{
	char *line;

	get_next_line(1, &line);
	return (line);
}

void print_pre_command()
{
	ft_putstr("minishell:");
	ft_putstr(get_cur_path());
	ft_putstr("> ");
}

int launch_commands(char *line, char **envp)
{
	t_cmd **cmds;
	int i;
	int status;

	i = 0;
	status = 0;
	cmds = parse_cmd(line);
	if (cmds)
	{
		while (cmds[i] && cmds[i]->cmd != END)
		{
			if (cmds[i]->cmd == PWD)
				start_pwd(cmds[i]->str); // complete
			else if (cmds[i]->cmd == UNKNOWN)
				start_unknown_cmd(cmds[i]->str); // complete
			else if (cmds[i]->cmd == ECHO)
				start_echo(cmds[i]->str); // Add '' "" $
			else if (cmds[i]->cmd == CD)
				start_cd(cmds[i]->str);
			else if (cmds[i]->cmd == EXPORT)
				start_export(cmds[i]->str);
			else if (cmds[i]->cmd == UNSET)
				start_unset(cmds[i]->str);
			else if (cmds[i]->cmd == ENV)// complete
				start_env(cmds[i]->str, envp);
			else if (cmds[i]->cmd == EXIT)// complete
				status = -1;
			free(cmds[i]->str);
			free(cmds[i]);
			i++;
			if (status == -1)
				{
				free(cmds);
				return (-1);
				}
		}
		free(cmds);
	}
	return(0);
}

int minishell(char **envp)
{
	char *line;
	int is_exit;
	int result;

	is_exit = 0;

	while (!is_exit)
	{
		print_pre_command();
		line = read_line();
		result = launch_commands(line, envp);
		if (line)
			free(line);
		if (result == -1)
			is_exit = 1;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{

	return (minishell(envp));
}
