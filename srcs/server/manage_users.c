/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_users.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:17:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:33:41 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	user_left(t_server *server, int fd)
{
	char	*chan;

	if ((chan = already_in_chan(server, fd)))
		leave_chan(server, fd, chan);
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
	if (new_fd < 10)
	{
		ft_strcpy(server->fds[new_fd].username, "vdarmaya");
		server->fds[new_fd].username[8] = new_fd + 48;
	}
	server->fds[new_fd].type = FD_CLIENT;
}

void	save_read(t_server *server, int fd, int ret)
{
	char	*tmp;
	size_t	len;

	len = 0;
	tmp = NULL;
	if (!server->fds[fd].save_read)
	{
		if (!(server->fds[fd].save_read = (char*)malloc(ret + 1)))
			ft_exiterror("Malloc failed", 1);
	}
	else
	{
		tmp = server->fds[fd].save_read;
		len += ft_strlen(tmp);
		if (!(server->fds[fd].save_read = (char*)malloc(len + ret + 1)))
			ft_exiterror("Malloc failed", 1);
		ft_strncpy(server->fds[fd].save_read, tmp, len);
	}
	ft_strncpy(server->fds[fd].save_read + len, server->fds[fd].buff_read, ret);
	server->fds[fd].save_read[len + ret] = '\0';
	if (tmp)
		free(tmp);
	ft_bzero(server->fds[fd].buff_read, BUFF_SIZE);
}
