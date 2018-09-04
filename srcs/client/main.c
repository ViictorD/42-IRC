/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:28:25 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/04 19:27:18 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	connect_server(t_client *client)
{
	struct protoent		*pe;
	struct sockaddr_in	addr;
	socklen_t			len;

	if (!(pe = getprotobyname("tcp")))
		ft_exiterror("Failed to  get the protocol name.", 1);
	if ((client->fd = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
		ft_exiterror("Failed to create server socket.", 1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = client->address;
	addr.sin_port = client->port;
	len = sizeof(addr);
	if ((connect(client->fd, (struct sockaddr*)&addr, len)) < 0)
		ft_exiterror("Failed to connect to the server.", 1);
}

void	manage_opt(int argc, char **argv, t_client *client)
{
	// FAIRE LES VERIFS SOLIDE POUR ARGV
	struct in_addr addr;

	++argv;
	inet_aton(*argv, &addr);
	client->address = addr.s_addr;
	++argv;
	if (argc == 3)
		client->port = htons(ft_atoi(*argv));
}

int		main(int argc, char **argv)
{
	t_client client;

	if (argc > 3)
		ft_exiterror("usage:\t./client [machine [port]]", 1);
	if (argc > 1)
		manage_opt(argc, argv, &client);
	connect_server(&client);
	return (0);
}