/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 19:34:35 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 17:00:16 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_send(t_client *client)
{
	int		ret;

	ret = send(client->fd, client->buff_write, irc_strlen(client->buff_write), 0);
	// ft_putstr("SENT: \"");
	// ft_putstr(client->buff_write);
	// ft_putstr("\"\n");
	if (ret < 0)
		lost_connection(client);
	else
		ft_bzero(client->buff_write, BUFF_SIZE);
}
