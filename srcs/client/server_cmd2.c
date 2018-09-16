/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:43:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:51:15 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	treat_number(t_client *client)
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
	PRINT_REPLY(num_msg, ERR_CANNOTSENDTOCHAN, \
		"Can not send to this channel\n");
	PRINT_REPLY(num_msg, ERR_NOSUCHSERVER, "Not in channel\n");
	PRINT_REPLY(num_msg, ERR_NOTONCHANNEL, "Not in channel\n");
	PRINT_REPLY(num_msg, ERR_NONICKSET, "Nickname not set !\n");
	PRINT_REPLY(num_msg, RPL_TOPIC, "Successful connected to the channel !\n");
	num_msg == RPL_WHOREPLY ? print_who(client->buff_read + 3) : 0;
}

void	treat_string(t_client *client, int ret)
{
	char	*cmd;

	if (client->save_read)
	{
		save_read_client(client, ret);
		cmd = client->save_read;
	}
	else
		cmd = client->buff_read;
	if (!ft_strncmp(cmd, "PRIVMSG", 7))
		print_privmsg(cmd);
	else if (!ft_strncmp(cmd, "CHANMSG", 7))
		print_chanmsg(cmd);
	else
	{
		ft_putstr("irc: bad message received from the server: \"");
		ft_putstr(client->buff_read);
		ft_putstr("\"\n");
	}
	if (client->save_read)
		ft_strdel(&client->save_read);
}
