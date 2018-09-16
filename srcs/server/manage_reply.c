/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_reply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:51:55 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:32:25 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	create_serv_resp2(t_server *server, int fd, char *msg1, char *msg2)
{
	size_t	inc;

	inc = 0;
	ft_strcpy(server->fds[fd].buff_write, msg1);
	inc += ft_strlen(msg1);
	if (msg2)
	{
		ft_strcpy(server->fds[fd].buff_write + inc, msg2);
		inc += ft_strlen(msg2);
	}
	ft_strcpy(server->fds[fd].buff_write + inc, "\r\n\0");
}

void		create_server_resp(t_server *server, int fd, char *msg1, char *msg2)
{
	size_t		inc;

	inc = ft_strlen(msg1);
	if (msg2)
		inc += ft_strlen(msg2);
	if (inc + 3 > BUFF_SIZE)
	{
		server->fds[fd].save_write = (char*)malloc(inc + 3);
		inc = 0;
		ft_strcpy(server->fds[fd].save_write, msg1);
		inc += ft_strlen(msg1);
		if (msg2)
		{
			ft_strcpy(server->fds[fd].save_write + inc, msg2);
			inc += ft_strlen(msg2);
		}
		ft_strcpy(server->fds[fd].save_write + inc, "\r\n\0");
	}
	else
		create_serv_resp2(server, fd, msg1, msg2);
}

void		reply_code_arg(t_server *server, int fd, int code, char *arg)
{
	char	*num;

	num = ft_itoa(code);
	create_cmd2(server->fds[fd].buff_write, num, arg);
	free(num);
}

void		reply_code(t_server *server, int fd, int code)
{
	char	*num;

	num = ft_itoa(code);
	create_cmd1(server->fds[fd].buff_write, num);
	free(num);
}
