/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_packet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 19:34:35 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:42:05 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_send(t_client *client)
{
	int		ret;

	ret = send(client->fd, client->buff_write, \
		irc_strlen(client->buff_write), 0);
	if (ret < 0)
		lost_connection(client);
	else
		ft_bzero(client->buff_write, BUFF_SIZE);
}

void	server_recv(t_client *client)
{
	int		ret;

	ret = recv(client->fd, client->buff_read, BUFF_SIZE, 0);
	if (ret <= 0)
		lost_connection(client);
	else if (ret == BUFF_SIZE)
		save_read_client(client, ret);
	else if (ret > 2 && ft_isdigit(client->buff_read[0]) && \
		ft_isdigit(client->buff_read[1]) && ft_isdigit(client->buff_read[2]))
		treat_number(client);
	else
		treat_string(client, ret);
	ft_bzero(client->buff_read, BUFF_SIZE);
}
