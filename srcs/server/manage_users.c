/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_users.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:50:40 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/04 17:20:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	user_left(t_server *server, int fd)
{
	close(fd);
	clean_fd(&server->fds[fd]);
	printf("Client #%d left the server.\n", fd);
}

void	create_new_user(t_server *server, int s)
{
	struct sockaddr_in	addr;
	int					new_fd;
	socklen_t			len;

	len = sizeof(addr);
	if ((new_fd = accept(s, (struct sockaddr*)&addr, &len)) < 0)
	{
		ft_fputstr("Fail to connect the new user.\n", 1);
		return ;
	}
	printf("New client #%d from %s:%d\n", new_fd, \
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	clean_fd(&server->fds[new_fd]);
	server->fds[new_fd].type = FD_CLIENT;
}

void	user_recv(t_server *server, int s)
{
	int		ret;
	int		i;

	// gerer si + grand que BUFF_SIZE
	ret = recv(s, server->fds[s].buff_read, BUFF_SIZE, 0);
	if (ret < 0)
		user_left(server, s);
	else
	{
		// On renvoie a tous les clients connecte le msg
		i = -1;
		while (++i < server->max_fd)
		{
			if (server->fds[i].type == FD_CLIENT && s != i)
				send(i, server->fds[s].buff_read, ret, 0);
		}
		ft_bzero(server->fds[s].buff_read, BUFF_SIZE + 1);
	}
}

void	user_send(t_server *server, int s)
{
	int		ret;

	ret = send(s, server->fds[s].buff_write, ft_strlen(server->fds[s].buff_write), 0);
	if (ret < 0)
		user_left(server, s);
	else
		ft_bzero(server->fds[s].buff_write, BUFF_SIZE + 1);
}