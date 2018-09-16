/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 15:56:01 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/14 16:46:25 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	send_to_channel(t_server *server, int fd, char *target, char *msg)
{
	t_chan	*chan;
	char	sharp;
	size_t	i;

	sharp = *target == '#' ? 1 : 0;
	chan = server->chan;
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, target + sharp))
		{
			i = 0;
			while (i < chan->count)
			{
				create_cmd3(server->fds[chan->connected[i]].buff_write, \
					"CHANMSG", server->fds[fd].username, msg);
				++i;
			}
		}
		NEXT(chan);
	}
}

char	user_exist(t_server *server, char *name)
{
	int		i;

	i = -1;
	while (++i < server->max_fd)
	{
		if (server->fds[i].type == FD_CLIENT && \
			!ft_strcmp(server->fds[i].username, name))
			return (1);
	}
	return (0);
}

static void	send_to_user(t_server *server, int fd, char *target, char *msg)
{
	int		i;

	if (user_exist(server, target))
	{
		i = -1;
		while (++i < server->max_fd)
		{
			if (server->fds[i].type == FD_CLIENT && \
				!ft_strcmp(server->fds[i].username, target))
			{
				create_cmd3(server->fds[i].buff_write, "PRIVMSG", \
					server->fds[fd].username, msg);
				return ;
			}
		}
	}
	else
		reply_code(server, fd, ERR_NOSUCHNICK);
}

static char	in_channel(t_server *server, int fd, char *name)
{
	t_chan	*chan;
	char	sharp;
	size_t	i;

	sharp = *name == '#' ? 1 : 0;
	chan = server->chan;
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, name + sharp))
		{
			i = 0;
			while (i < chan->count)
			{
				if (chan->connected[i] == fd)
					return (1);
				++i;
			}
			return (0);
		}
		NEXT(chan);
	}
	return (0);
}

void		manage_msg(t_server *server, int fd)
{
	char	*tmp;
	char	*target;
	char	*msg;

	tmp = server->fds[fd].buff_read + 3;
	target = get_next_word(&tmp);
	if (!target)
	{
		reply_code(server, fd, ERR_NORECIPIENT);
		return ;
	}
	msg = pass_whitespace(tmp);
	if (!msg)
	{
		reply_code(server, fd, ERR_NOTEXTTOSEND);
		free(target);
		return ;
	}
	if (chan_exist(server, target))
	{
		if (!in_channel(server, fd, target))
			reply_code(server, fd, ERR_CANNOTSENDTOCHAN);
		else
			send_to_channel(server, fd, target, msg);
	}
	else
		send_to_user(server, fd, target, msg);
	free(target);
}