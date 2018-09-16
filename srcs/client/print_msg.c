/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:22:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:42:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	write_line(char is_priv, char *user, char *msg)
{
	time_t		now;
	struct tm	*t;

	now = time(NULL);
	t = localtime(&now);
	ft_putchar('[');
	ft_putnbr(t->tm_hour);
	ft_putchar(':');
	ft_putnbr(t->tm_min);
	ft_putchar(':');
	ft_putnbr(t->tm_sec);
	ft_putstr("] ");
	if (is_priv)
		ft_putstr("PRIVATE ");
	ft_putstr(": <");
	ft_putstr(user);
	ft_putstr("> ");
	ft_putstr(msg);
	ft_putstr("\n");
}

void		print_privmsg(char *cmd)
{
	char		*tmp;
	char		*from;
	char		*msg;

	cmd[irc_strlen(cmd) - 2] = 0;
	cmd[irc_strlen(cmd) - 1] = 0;
	tmp = cmd + 7;
	from = get_next_word(&tmp);
	msg = pass_whitespace(tmp);
	if (!from || !msg)
	{
		ft_putstr("Bad private message received\n");
		return ;
	}
	write_line(1, from, msg);
	free(from);
}

void		print_chanmsg(char *cmd)
{
	char		*tmp;
	char		*from;
	char		*msg;

	cmd[irc_strlen(cmd) - 2] = 0;
	cmd[irc_strlen(cmd) - 1] = 0;
	tmp = cmd + 7;
	from = get_next_word(&tmp);
	msg = pass_whitespace(tmp);
	if (!from || !msg)
	{
		ft_putstr("Bad channel message received\n");
		return ;
	}
	write_line(0, from, msg);
	free(from);
}
