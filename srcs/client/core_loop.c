/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:40:18 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:40:37 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	check_client_fds(t_client *client)
{
	if (FD_ISSET(0, &client->fd_read))
		manage_cmd(client);
	if (client->fd > 0 && FD_ISSET(client->fd, &client->fd_read))
		server_recv(client);
	if (client->fd > 0 && FD_ISSET(client->fd, &client->fd_write))
		server_send(client);
}

void		client_loop(t_client *client)
{
	int		max;

	while (1)
	{
		FD_ZERO(&client->fd_read);
		FD_ZERO(&client->fd_write);
		FD_SET(0, &client->fd_read);
		if (client->fd != 0)
		{
			FD_SET(client->fd, &client->fd_read);
			if (irc_strlen(client->buff_write))
				FD_SET(client->fd, &client->fd_write);
		}
		max = client->fd > 0 ? client->fd : 0;
		select(max + 1, &client->fd_read, &client->fd_write, NULL, NULL);
		check_client_fds(client);
	}
}
