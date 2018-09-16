/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:04:47 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 15:20:17 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	create_server(t_server *server, int port)
{
	struct protoent	*pe;
	struct sockaddr_in addr;
	int				fd;

	if (!(pe = getprotobyname("tcp")))
		ft_exiterror("Failed to  get the protocol name.", 1);
	if ((fd = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
		ft_exiterror("Failed to create server socket.", 1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if ((bind(fd, (struct sockaddr*)&addr, sizeof(addr))) < 0)
		ft_exiterror("Failed to bind the socket.", 1);
	if ((listen(fd, 5)) < 0)
		ft_exiterror("Failed to set the socket on listen.", 1);
	server->fds[fd].type = FD_SERV;
}

void	clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	ft_bzero(fd->buff_read, BUFF_SIZE);
	ft_bzero(fd->buff_write, BUFF_SIZE);
	ft_bzero(fd->username, 10);
}

static void	init_struct(t_server *server)
{
	struct rlimit	rlp;
	int				i;

	if (getrlimit(RLIMIT_NOFILE, &rlp) < 0)
		ft_exiterror("Failed to get fd limits.", 1);
	server->max_fd = rlp.rlim_cur;
	if (!(server->fds = malloc(sizeof(struct s_fd) * server->max_fd)))
		ft_exiterror("Malloc failed on init.", 1);
	i = -1;
	while (++i < server->max_fd)
		clean_fd(&server->fds[i]);
	server->chan = NULL;
}

int			main(int argc, char **argv)
{
	t_server	server;

	if (argc < 2)
		ft_exiterror("usage:\t./server <port>", 1);
	// recup le nombre max de fd qu'on peux ouvrir
	init_struct(&server);
	// creer le socket d'ecoute
	create_server(&server, ft_atoi(*++argv));
	// while loop sur le select
	server_loop(&server);
	return (0);
}
