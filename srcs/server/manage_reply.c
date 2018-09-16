/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_reply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:51:55 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 15:59:01 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	reply_code_arg(t_server *server, int fd, int code, char *arg)
{
	char	*num;

	num = ft_itoa(code);
	create_cmd2(server->fds[fd].buff_write, num, arg);
	free(num);
}

void	reply_code(t_server *server, int fd, int code)
{
	char	*num;

	num = ft_itoa(code);
	create_cmd1(server->fds[fd].buff_write, num);
	free(num);
}
