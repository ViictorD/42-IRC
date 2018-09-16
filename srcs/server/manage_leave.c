/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_leave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:26:24 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/14 16:02:35 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	reindex_connected(t_chan *chan, size_t i)
{
	while (i < chan->count)
	{
		chan->connected[i] = chan->connected[i + 1];
		++i;
	}
	chan->connected[i] = 0;
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
				if (chan->connected[i] == fd)
				{
					ft_putstr("Removed user #");
					ft_putnbr(fd);
					ft_putstr(" from \"");
					ft_putstr(name);
					ft_putstr("\"\n");
					chan->connected[i] = 0;
					--chan->count;
					if (!chan->count)
						delete_chan(server, chan);
					else if (i != chan->count)
						reindex_connected(chan, i);
					return ;
				}
				++i;
			}
		}
		NEXT(chan);
	}
	return ;
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
				notif_users(server, fd, chan, 0);
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

void		manage_leave(t_server *server, int fd)
{
	char	*name;

	name = server->fds[fd].buff_read + 5;
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
