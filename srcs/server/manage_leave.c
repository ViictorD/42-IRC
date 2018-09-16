/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_leave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:26:24 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:14:41 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static char	leave_chan2(t_server *server, int fd, size_t i, t_chan *chan)
{
	ft_putstr("Removed user #");
	ft_putnbr(fd);
	print_sentence3(" from \"", chan->chan_name, "\"");
	notif_users(server, fd, chan, 0);
	chan->connected[i] = 0;
	--chan->count;
	if (!chan->count)
		delete_chan(server, chan);
	else if (i != chan->count)
		reindex_connected(chan, i);
	return (1);
}

void		leave_chan(t_server *server, int fd, char *name)
{
	t_chan	*chan;
	size_t	i;
	char	sharp;

	sharp = *name == '#' ? 1 : 0;
	chan = server->chan;
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, name + sharp))
		{
			i = 0;
			while (i < chan->count)
			{
				if (chan->connected[i] == fd && \
					leave_chan2(server, fd, i, chan))
					return ;
				++i;
			}
		}
		NEXT(chan);
	}
}

static char	leave_all(t_server *server, int fd)
{
	t_chan	*chan;
	size_t	i;

	chan = server->chan;
	while (chan)
	{
		i = 0;
		while (i < chan->count)
		{
			if (chan->connected[i] == fd)
			{
				leave_chan(server, fd, chan->chan_name);
				return (1);
			}
			++i;
		}
		NEXT(chan);
	}
	return (0);
}

static char	is_in_chan(t_server *server, int fd, char *name)
{
	t_chan	*chan;
	size_t	i;
	char	sharp;

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
		}
		NEXT(chan);
	}
	return (0);
}

void		manage_leave(t_server *server, int fd, char *cmd)
{
	char	*name;

	name = cmd + 6;
	name = get_next_word(&name);
	if (name)
	{
		if (is_in_chan(server, fd, name))
			leave_chan(server, fd, name);
		else
			reply_code(server, fd, ERR_NOTONCHANNEL);
		free(name);
	}
	else
	{
		if (!leave_all(server, fd))
			reply_code(server, fd, ERR_NOTONCHANNEL);
	}
}
