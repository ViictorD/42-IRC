/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_recv_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 14:07:01 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 18:08:16 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void		manage_recv_cmd(t_server *server, int fd, int ret)
{
	char	*cmd;

	if (server->fds[fd].save_read)
	{
		save_read(server, fd, ret);
		cmd = server->fds[fd].save_read;
	}
	else
		cmd = server->fds[fd].buff_read;
	if (!ft_strncmp(cmd, "/nick", 5))
		manage_nick(server, fd, cmd);
	else if (!ft_strncmp(cmd, "/who", 4))
		manage_who(server, fd);
	else if (!ft_strncmp(cmd, "/join", 5))
		manage_join(server, fd, cmd);
	else if (!ft_strncmp(cmd, "/leave", 6))
		manage_leave(server, fd, cmd);
	else if (!ft_strncmp(cmd, "/msg", 4))
		manage_msg(server, fd, cmd);
	if (server->fds[fd].save_read)
		ft_strdel(&server->fds[fd].save_read);
}
