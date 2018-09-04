/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:04:13 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/04 19:10:39 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include <netdb.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "../libft/libft.h"

# define BUF_SIZE	4096

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

/*
** ---------------------------------- SERVER ----------------------------------
*/

typedef struct		s_fd
{
	int				type;
	char			buff_read[BUF_SIZE + 1];
	char			buff_write[BUF_SIZE + 1];
}					t_fd;

typedef struct		s_server
{
	t_fd			*fds;
	int				max_fd;
	fd_set			fd_read;
	fd_set			fd_write;

}					t_server;

void	server_loop(t_server *server);
void	clean_fd(t_fd *fd);
void	create_new_user(t_server *server, int s);
void	user_recv(t_server *server, int s);
void	user_send(t_server *server, int s);

/*
** ---------------------------------- CLIENT ----------------------------------
*/

typedef struct	s_client
{
	int			fd;
	uint		address;
	int			port;
}				t_client;

#endif
