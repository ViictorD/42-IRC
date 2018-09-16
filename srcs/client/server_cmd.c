/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 19:11:31 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/14 15:59:28 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void			lost_connection(t_client *client)
{
	ft_putstr("\nLost connection with the server\n");
	clear_client(client);
}

static	void	treat_number(t_client *client)
{
	int		num_msg;
	char	num[4];

	ft_strncpy(num, client->buff_read, 3);
	num[3] = 0;
	num_msg = ft_atoi(num);
	PRINT_REPLY(num_msg, 0, "Fail to get the packet id\n");
	PRINT_REPLY(num_msg, ERR_NONICKNAMEGIVEN, "No nickname given\n");
	PRINT_REPLY(num_msg, ERR_UNAVAILRESOURCE, "Invalid size\n");
	PRINT_REPLY(num_msg, ERR_NICKCOLLISION, "Nickname already exist\n");
	PRINT_REPLY(num_msg, ERR_NOSUCHNICK, "User not found\n");
	PRINT_REPLY(num_msg, ERR_NEEDMOREPARAMS, "Need more parameter\n");
	PRINT_REPLY(num_msg, ERR_TOOMANYCHANNELS, "Too many channels\n");
	PRINT_REPLY(num_msg, ERR_NORECIPIENT, "No target\n");
	PRINT_REPLY(num_msg, ERR_NOTEXTTOSEND, "No message to send\n");
	PRINT_REPLY(num_msg, ERR_CANNOTSENDTOCHAN, "Can not send to this channel\n");
	PRINT_REPLY(num_msg, ERR_NOSUCHSERVER, "Not in channel\n");
	PRINT_REPLY(num_msg, ERR_NOTONCHANNEL, "Not in channel\n");
	PRINT_REPLY(num_msg, ERR_NONICKSET, "Nickname not set !\n");
	PRINT_REPLY(num_msg, RPL_TOPIC, "Successful connected to the channel !\n");
	
	client->prompt = num_msg == RPL_TOPIC ? 0 : 1;

	num_msg == RPL_WHOREPLY ? print_who(client->buff_read + 3) : 0;
	if (client->wait_data && num_msg)
		client->wait_data = 0;
}

static	void	treat_string(t_client *client)
{
	if (!ft_strncmp(client->buff_read, "PRIVMSG", 7))
		print_privmsg(client);
	else if (!ft_strncmp(client->buff_read, "CHANMSG", 7))
		print_chanmsg(client);
	else
	{
		ft_putstr("irc: bad message received from the server: \"");
		ft_putstr(client->buff_read);
		ft_putstr("\"\n");
	}
}

void	server_recv(t_client *client)
{
	int		ret;

	ret = recv(client->fd, client->buff_read, BUFF_SIZE, 0);
	// ft_putstr("RECV: \"");
	// ft_putstr(client->buff_read);
	// ft_putstr("\"\n");
	if (ret <= 0)
	{
		lost_connection(client);
		return ;
	}
	if (ret > 2 && ft_isdigit(client->buff_read[0]) && \
		ft_isdigit(client->buff_read[1]) && ft_isdigit(client->buff_read[2]))
		treat_number(client);
	else
		treat_string(client);
	ft_bzero(client->buff_read, BUFF_SIZE);
}
