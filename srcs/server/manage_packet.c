/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_packet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:32:48 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:33:57 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	user_recv(t_server *server, int s)
{
	int		ret;
	int		i;

	i = ft_strlen(server->fds[s].buff_read);
	ret = recv(s, server->fds[s].buff_read + i, BUFF_SIZE - i, 0);
	if (ret <= 0)
		user_left(server, s);
	else if (ret == BUFF_SIZE - i)
		save_read(server, s, ret + i);
	else if (server->fds[s].buff_read[ret + i - 1] != '\n')
		;
	else
	{
		if (server->fds[s].buff_read[ret + i - 2] != '\r')
		{
			server->fds[s].buff_read[ret + i - 1] = '\r';
			server->fds[s].buff_read[ret + i] = '\n';
		}
		manage_recv_cmd(server, s, ret);
		ft_bzero(server->fds[s].buff_read, BUFF_SIZE);
	}
}

void	user_send(t_server *server, int s)
{
	int		ret;

	if (server->fds[s].save_write)
	{
		ret = ft_strlen(server->fds[s].save_write) > BUFF_SIZE ? BUFF_SIZE : \
			ft_strlen(server->fds[s].save_write);
		ft_strncpy(server->fds[s].buff_write, server->fds[s].save_write, ret);
		if (ret == BUFF_SIZE)
		{
			ft_memcpy(server->fds[s].save_write, server->fds[s].save_write + \
				ret, ft_strlen(server->fds[s].save_write) - ret + 1);
		}
		else
			ft_strdel(&server->fds[s].save_write);
		ret = send(s, server->fds[s].buff_write, ret, 0);
	}
	else
		ret = send(s, server->fds[s].buff_write, \
			irc_strlen(server->fds[s].buff_write), 0);
	if (ret < 0)
		user_left(server, s);
	else
		ft_bzero(server->fds[s].buff_write, BUFF_SIZE);
}
