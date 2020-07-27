/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:03:37 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:03:51 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_echo(char *line)
{
	char *prt;

	prt = ft_strdup((line + skip_whitespace(line)));
	if (start_with(prt, "-n"))
		ft_putstr((prt + 2 + skip_whitespace(line)));
	else
	{
		ft_putstr((line + skip_whitespace(line)));
		ft_putstr("\n");
	}
	free(prt);
	return (0);
}
