/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_recv_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 14:07:01 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 15:00:08 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void		manage_recv_cmd(t_server *server, int fd)
{
	if (!ft_strncmp(server->fds[fd].buff_read, "NICK", 4))
		manage_nick(server, fd);
	else if (!ft_strncmp(server->fds[fd].buff_read, "WHO", 3))
		manage_who(server, fd);
	else if (!ft_strncmp(server->fds[fd].buff_read, "JOIN", 4))
		manage_join(server, fd);
	else if (!ft_strncmp(server->fds[fd].buff_read, "LEAVE", 5))
		manage_leave(server, fd);
	else if (!ft_strncmp(server->fds[fd].buff_read, "MSG", 3))
		manage_msg(server, fd);
}
