/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:28:25 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 16:52:40 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

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