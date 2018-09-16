/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:50:21 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:07:13 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	join_chan(t_server *server, int fd, char *name)
{
	t_chan	*chan;
	char	sharp;

	sharp = *name == '#' ? 1 : 0;
	chan = server->chan;
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, name + sharp))
		{
			chan->connected[chan->count] = fd;
			++chan->count;
			notif_users(server, fd, chan, 1);
			return ;
		}
		NEXT(chan);
	}
}

static void	manage_join2(t_server *server, int fd, char *name)
{
	char	*curr_chan;

	if ((curr_chan = already_in_chan(server, fd)))
		leave_chan(server, fd, curr_chan);
	if (!chan_exist(server, name))
		create_chan(server, name);
	join_chan(server, fd, name);
	ft_putstr("User #");
	ft_putnbr(fd);
	print_sentence2(" has join the channel: ", name);
}

void		notif_users(t_server *server, int fd, t_chan *chan, char is_join)
{
	size_t	i;
	char	msg[35];

	i = 0;
	ft_bzero(msg, 35);
	while (i < chan->count)
	{
		ft_strcpy(msg, "User ");
		ft_strcpy(msg + 5, server->fds[fd].username);
		if (is_join)
			ft_strcpy(msg + ft_strlen(server->fds[fd].username) + 5, \
				" has join the channel");
		else
			ft_strcpy(msg + ft_strlen(server->fds[fd].username) + 5, \
						" has left the channel");
		create_cmd3(server->fds[chan->connected[i]].buff_write, \
			"CHANMSG", "server", msg);
		ft_bzero(msg, 35);
		++i;
	}
}

char		*already_in_chan(t_server *server, int fd)
{
	size_t	i;
	t_chan	*chan;

	chan = server->chan;
	while (chan)
	{
		i = 0;
		while (i < chan->count)
		{
			if (chan->connected[i] == fd)
				return (chan->chan_name);
			++i;
		}
		NEXT(chan);
	}
	return (NULL);
}

void		manage_join(t_server *server, int fd, char *cmd)
{
	char	*tmp;
	char	*name;

	tmp = cmd + 5;
	name = get_next_word(&tmp);
	if (!name)
	{
		reply_code(server, fd, ERR_NEEDMOREPARAMS);
		return ;
	}
	if (*tmp != '\r')
		reply_code(server, fd, ERR_TOOMANYCHANNELS);
	else if (ft_strlen(name) > 50)
		reply_code(server, fd, ERR_UNAVAILRESOURCE);
	else if (*server->fds[fd].username == '\0')
		reply_code(server, fd, ERR_NONICKSET);
	else if (user_exist(server, name))
		reply_code(server, fd, ERR_NICKCOLLISION);
	else
		manage_join2(server, fd, name);
	free(name);
}
