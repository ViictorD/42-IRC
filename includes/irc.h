/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:04:13 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:53:42 by vdarmaya         ###   ########.fr       */
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
# include <time.h>
# include "../libft/libft.h"
# include "numcode.h"

# define BUFF_SIZE	512
# define CMD_BUFF	512
# define TIMEOUT	3

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define DEF_PORT	4242

# define PRINT_REPLY(code, code2, msg)	code == code2 ? ft_putstr(msg) : 0

# define NEXT(a)							a = a->next

/*
** ---------------------------------- SERVER ----------------------------------
*/

typedef struct		s_fd
{
	int				type;
	char			buff_read[BUFF_SIZE];
	char			*save_read;
	char			buff_write[BUFF_SIZE];
	char			*save_write;
	char			username[10];
}					t_fd;

typedef struct		s_chan
{
	char			chan_name[50];
	int				*connected;
	size_t			count;
	struct s_chan	*next;
}					t_chan;

typedef struct		s_server
{
	t_fd			*fds;
	t_chan			*chan;
	int				max_fd;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_server;

void				server_loop(t_server *server);
void				clean_fd(t_fd *fd);
void				create_new_user(t_server *server, int s);
void				user_recv(t_server *server, int s);
void				user_send(t_server *server, int s);
void				create_cmd1(char *dest, char *arg1);
void				create_cmd2(char *dest, char *arg1, char *arg2);
void				create_cmd3(char *dest, char *arg1, char *arg2, char *arg3);
void				user_left(t_server *server, int fd);
void				manage_recv_cmd(t_server *server, int fd, int ret);
void				reply_code(t_server *server, int fd, int code);
void				manage_nick(t_server *server, int fd, char *cmd);
void				manage_who(t_server *server, int fd);
void				reply_code_arg(t_server *server, int fd, int code, \
						char *arg);
void				manage_join(t_server *server, int fd, char *cmd);
char				chan_exist(t_server *server, char *name);
void				create_chan(t_server *server, char *name);
void				manage_leave(t_server *server, int fd, char *cmd);
void				delete_chan(t_server *server, t_chan *to_del);
void				manage_msg(t_server *server, int fd, char *cmd);
char				*pass_whitespace(char *msg);
void				leave_chan(t_server *server, int fd, char *name);
char				*already_in_chan(t_server *server, int fd);
void				notif_users(t_server *server, int fd, t_chan *chan, \
						char is_join);
char				user_exist(t_server *server, char *nick);
void				save_read(t_server *server, int fd, int ret);
void				create_server_resp(t_server *server, int fd, char *msg1, \
						char *msg2);
void				print_sentence2(char *str1, char *str2);
void				print_sentence3(char *str1, char *str2, char *str3);
void				reindex_connected(t_chan *chan, size_t i);

/*
** ---------------------------------- CLIENT ----------------------------------
*/

typedef struct		s_client
{
	int				fd;
	uint			address;
	int				port;
	fd_set			fd_read;
	fd_set			fd_write;
	char			buff_read[BUFF_SIZE];
	char			*save_read;
	char			buff_write[BUFF_SIZE];
}					t_client;

void				connect_server(t_client *client);
void				print_usage(char *str);
void				connect_usage(void);
void				manage_connect(char *str, t_client *client);
void				clear_client(t_client *client);
void				client_loop(t_client *client);
char				*get_next_word(char **str);
void				server_send(t_client *client);
void				server_recv(t_client *client);
void				lost_connection(t_client *client);
void				print_who(char *str);
void				print_help(void);
void				print_privmsg(char *cmd);
void				print_chanmsg(char *cmd);
void				save_read_client(t_client *client, int ret);
void				treat_number(t_client *client);
void				treat_string(t_client *client, int ret);
void				manage_cmd(t_client *client);

#endif
