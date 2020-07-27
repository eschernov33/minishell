/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 21:13:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 22:29:06 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_bad_quotes(char *str)
{
	char *res;
	int count;
	int i;
	int j;
	int open_quote;

	res = malloc(ft_strlen(str) + 1);
	count = 0;
	i = 0;
	j = 0;
	open_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i-1] != '\\'))
			count++;
		else if (str[i] == '"' && !open_quote && (!str[i+1] || str[i+1] != '$'))
			count++;
		else if (str[i] == '"' && open_quote == 1)
			{
				str[j] = str[i];
				j++;
				open_quote = 0;
			}
		else if (str[i] == '"' && str[i+1] && str[i+1] == '$')
			{
				str[j] = str[i];
				j++;
				open_quote = 1;
			}
		else
			{
			str[j] = str[i];
				j++;
			}
		i++;
	}
	str[j] = '\0';
	return (str);

}

char *get_path_name(char *str)
{
	int i;

	i = 0;

	while (str[i] && str[i] != '"')
		i++;

	return ft_substr(str, 1, i-1);
}


char *change_envs(char *str, char **envr)
{
	int i;
	char *res;
	char *param;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"' && str[i+1] && str[i+1] == '$')
		{
			param = get_line_env(envr, get_path_name(str+1));
			printf("param %s\n", param);
			if (param != NULL)
				res = ft_strjoin(res , param + ft_strlen(get_path_name(str+1)));
		} else if (str[i] != '"')
				res[ft_strlen(res)] = str[i];

		i++;

	}
	res[i] = '\0';
	return res;
}

char *correct_echo_msg(char **str, char **envr)
{
	char *res;

	res = remove_bad_quotes(*str);
	res = change_envs(res, envr);
	free(*str);
	*str = res;

	return res;



}
