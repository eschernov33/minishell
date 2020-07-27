/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 23:35:05 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_strswap(char **strs, int i1, int i2)
{
	char		*tmp;

	tmp = strs[i1];
	strs[i1] = strs[i2];
	strs[i2] = tmp;

}

void sort_and_show(char **envp)
{
	int is_sort = 0;
	int i = 0;

	while(envp[i] && envp[i+1])
	{
		if (ft_strcmp(envp[i], envp[i+1]) > 0)
		{
			ft_strswap(envp, i, i+1);
			is_sort = 1;
		}
		i++;
	}
	if (is_sort)
		sort_and_show(envp);
	else
	{
		while (*envp)
		{
			ft_putstr(*envp);
			ft_putstr("\n");

			envp++;
		}
	}
}

int start_export(char *line, char **envp)
{
	if (!line || !line[skip_whitespace(line)])
	{
		sort_and_show(envp);
	}
	//else if





	return(0);
}
