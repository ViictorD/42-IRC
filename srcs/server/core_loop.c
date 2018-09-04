/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:58:45 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/04 17:18:26 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	reset_fd(t_server *server, int *max)
{
	int		i;

	FD_ZERO(&server->fd_read);
	FD_ZERO(&server->fd_write);
	*max = 0;
	i = -1;
	while (++i < server->max_fd)
	{
		if (server->fds[i].type != FD_FREE)
		{
			FD_SET(i, &server->fd_read);
			if (*(server->fds[i].buff_write) != 0)
				FD_SET(i, &server->fd_write);
			*max = (i > *max) ? i : *max;
		}
	}
}

static void	check_fds(t_server *server, int ret)
{
	int		i;

	i = -1;
	while (++i < server->max_fd && ret > 0)
	{
		if (FD_ISSET(i, &server->fd_read))
		{
			if (server->fds[i].type == FD_SERV)
				create_new_user(server, i);
			else
				user_recv(server, i);
			--ret;
		}
		if (FD_ISSET(i, &server->fd_write))
		{
			user_send(server, i);
			--ret;
		}
	}
}

void		server_loop(t_server *server)
{
	int		max;
	int		ret;

	while (42)
	{
		reset_fd(server, &max);
		ret = select(max + 1, &server->fd_read, &server->fd_write, NULL, NULL);
		check_fds(server, ret);
	}
}