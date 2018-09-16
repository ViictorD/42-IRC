/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:44:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 18:42:13 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	print_usage(char *str)
{
	ft_fputstr("irc: command not found: ", 2);
	ft_fputstr(str, 2);
	ft_fputstr("\n", 2);
	ft_fputstr("type \"/help\" to see the usage\n", 2);
}

void	connect_usage(void)
{
	ft_fputstr("irc: invalide parameter\n", 2);
	ft_fputstr("usage: /connect <machine> [port]\n", 2);
}

void	print_who(char *str)
{
	char		*save;

	while (*str && *str != '\r' && *(str + 1) != '\n')
	{
		while (*str && *str == ' ')
			++str;
		save = str;
		while (*str && *str != ' ' && !(*str == '\r' && *(str + 1) == '\n'))
			++str;
		if (!(str - save))
			return ;
		write(1, save, str - save);
		ft_putchar('\n');
	}
}

void	print_help(void)
{
	ft_putstr("\x1B[4m");
	ft_putstr("\nList of commands:\n\n");
	ft_putstr("\x1B[0m");
	ft_putstr("  - /connect <machine> [port]\n");
	ft_putstr("  - /join <#chan>\n");
	ft_putstr("  - /leave [#chan]\n");
	ft_putstr("  - /msg <nick> <message>\n");
	ft_putstr("  - /nick <nick>\n");
	ft_putstr("  - /who\n\n");
}