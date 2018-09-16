/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:28:25 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:45:40 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	clear_client(t_client *client)
{
	if (client->fd)
		close(client->fd);
	client->fd = 0;
	client->address = 0;
	client->port = 0;
	ft_bzero(client->buff_read, BUFF_SIZE);
	ft_bzero(client->buff_write, BUFF_SIZE);
	client->save_read = NULL;
}

void	manage_opt(int argc, char **argv, t_client *client)
{
	struct in_addr	addr;
	int				port;

	++argv;
	if (!inet_aton(*argv, &addr))
		ft_exiterror("usage:\t./client [machine [port]]", 1);
	client->address = addr.s_addr;
	++argv;
	if (argc == 3)
	{
		if (!(port = ft_atoi(*argv)))
			ft_exiterror("usage:\t./client [machine [port]]", 1);
		client->port = htons(port);
	}
	else
		client->port = htons(DEF_PORT);
}

int		main(int argc, char **argv)
{
	t_client client;

	if (argc > 3)
		ft_exiterror("usage:\t./client [machine [port]]", 1);
	clear_client(&client);
	if (argc > 1)
	{
		manage_opt(argc, argv, &client);
		connect_server(&client);
	}
	client_loop(&client);
	return (0);
}
