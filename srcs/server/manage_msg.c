/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 15:56:01 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:21:41 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	send_to_channel(t_server *server, int fd, char *target, char *msg)
{
	t_chan	*chan;
	char	sharp;
	size_t	i;
	char	tmp[19];

	sharp = *target == '#' ? 1 : 0;
	chan = server->chan;
	ft_strcpy(tmp, "CHANMSG ");
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, target + sharp))
		{
			i = 0;
			while (i < chan->count)
			{
				ft_strcpy(tmp + 8, server->fds[fd].username);
				ft_strcpy(tmp + 8 + ft_strlen(server->fds[fd].username), " \0");
				create_server_resp(server, chan->connected[i], tmp, msg);
				++i;
			}
		}
		NEXT(chan);
	}
}

static void	send_to_user(t_server *server, int fd, char *target, char *msg)
{
	int		i;
	char	tmp[19];

	if (user_exist(server, target))
	{
		i = -1;
		while (++i < server->max_fd)
		{
			if (server->fds[i].type == FD_CLIENT && \
				!ft_strcmp(server->fds[i].username, target))
			{
				ft_strcpy(tmp, "PRIVMSG ");
				ft_strcpy(tmp + 8, server->fds[fd].username);
				ft_strcpy(tmp + 8 + ft_strlen(server->fds[fd].username), " \0");
				create_server_resp(server, i, tmp, msg);
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

static void	manage_msg2(t_server *server, int fd, char *target, char *msg)
{
	if (chan_exist(server, target))
	{
		if (!in_channel(server, fd, target))
			reply_code(server, fd, ERR_CANNOTSENDTOCHAN);
		else
			send_to_channel(server, fd, target, msg);
	}
	else
		send_to_user(server, fd, target, msg);
}

void		manage_msg(t_server *server, int fd, char *cmd)
{
	char	*tmp;
	char	*target;
	char	*msg;

	tmp = cmd + 4;
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
	manage_msg2(server, fd, target, msg);
	free(target);
}
