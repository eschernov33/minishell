/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_unknown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:04:17 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:04:30 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_unknown_cmd(char *line)
{
	char *tmp;

	tmp = ft_strcdup(line, ' ');
	ft_putstr("minishell: command not found: ");
	ft_putstr(tmp);
	ft_putstr("\n");
	free(tmp);
	return (0);
}
