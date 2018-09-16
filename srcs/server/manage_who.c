/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_who.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:08:18 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 17:04:19 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static t_chan	*in_all_chan(t_server *server, int fd)
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
				return (chan);
			++i;
		}
		NEXT(chan);
	}
	return (NULL);
}

void		manage_who(t_server *server, int fd)
{
	char	users[BUFF_SIZE - 4];
	size_t	i;
	size_t	count;
	t_chan	*chan;

	if (!(chan = in_all_chan(server, fd)))
	{
		reply_code(server, fd, ERR_NOSUCHSERVER);
		return ;
	}
	ft_bzero(users, BUFF_SIZE - 4);
	count = 0;
	i = 0;
	while (i < chan->count)
	{
		if (count + ft_strlen(server->fds[chan->connected[i]].username) > BUFF_SIZE - 4)
			break ;
		ft_strcpy(users + count, server->fds[chan->connected[i]].username);
		count += ft_strlen(server->fds[chan->connected[i]].username);
		ft_strcpy(users + count, " ");
		++count;
		++i;
	}

	users[count] = '\0';
	reply_code_arg(server, fd, RPL_WHOREPLY, users);
}
