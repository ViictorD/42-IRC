/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_users.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:17:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 13:21:17 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.h"

void	user_left(t_server *server, int fd)
{
	close(fd);
	clean_fd(&server->fds[fd]);
	ft_putstr("Client #");
	ft_putnbr(fd);
	ft_putstr(" left the server.\n");
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
	ft_putstr("New client #");
	ft_putnbr(new_fd);
	ft_putstr(" from \"");
	ft_putstr(inet_ntoa(addr.sin_addr));
	ft_putstr(":");
	ft_putnbr(ntohs(addr.sin_port));
	ft_putstr("\"\n");
	clean_fd(&server->fds[new_fd]);
	server->fds[new_fd].type = FD_CLIENT;
}

void	user_recv(t_server *server, int s)
{
	int		ret;
	// int		i;

	// gerer si + grand que BUFF_SIZE
	ret = recv(s, server->fds[s].buff_read, BUFF_SIZE, 0);
	if (ret <= 0)
		user_left(server, s);
	else
	{
		manage_recv_cmd(server, s);
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