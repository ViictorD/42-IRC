
#include "irc.h"

static char	check_cmd(char *str, char *cmp)
{
	size_t	size;

	size = ft_strlen(cmp);
	if (*str == '/' && !ft_strncmp(str + 1, cmp, size) && \
		(*(str + 1 + size) == ' ' || *(str + 1 + size) == '\0'))
			return (1);
	return (0);
}

static void	manage_cmd(t_client *client)
{
	char	str[CMD_BUFF];
	int		i;

	i = read(0, str, CMD_BUFF);
	if (!i || i == 1)
	{
		!i ? ft_putchar('\n') : 0;
		return ;
	}
	if (i == CMD_BUFF)
	{
		ft_fputstr("irc: command too long\n", 2);
		while (str[0] != 10)
			read(0, str, 1);
		return ;
	}
	str[i - 1] = '\0';
	// if (*str == '/' &&!ft_strncmp(str + 1, "nick", 4) || \
	// 	!ft_strncmp(str + 1, "join", 4) || !ft_strncmp(str + 1, "who", 3) || \
	// 	!ft_strncmp(str + 1, "msg", 3) || !ft_strncmp(str + 1, "leave", 5))
	if (check_cmd(str, "nick") || check_cmd(str, "join") || \
		check_cmd(str, "who") || check_cmd(str, "msg") || \
		check_cmd(str, "leave"))
	{
		if (!client->fd)
			ft_fputstr("Not connected to a server\n", 2);
		else
		{
			if (!ft_strncmp(str + 1, "leave", 5))
				create_cmd2(client->buff_write, "LEAVE", str + 6);
			else if (!ft_strncmp(str + 1, "nick", 4))
				create_cmd2(client->buff_write, "NICK", str + 5);
			else if (!ft_strncmp(str + 1, "join", 4))
				create_cmd2(client->buff_write, "JOIN", str + 5);
			else if (!ft_strncmp(str + 1, "who", 4))
				create_cmd2(client->buff_write, "WHO", str + 4);
			else
				create_cmd2(client->buff_write, "MSG", str + 4);
			client->wait_data = 1;
		}
	}
	else
	{
		if (!ft_strncmp(str + 1, "connect", 7))
			manage_connect(str + 8, client);
		else if (!ft_strcmp(str + 1, "help"))
			print_help();
		else
			print_usage(str);
	}
}

void	clear_client(t_client *client)
{
	if (client->fd)
		close(client->fd);
	client->fd = 0;
	client->address = 0;
	client->port = 0;
	ft_bzero(client->buff_read, BUFF_SIZE);
	ft_bzero(client->buff_write, BUFF_SIZE);
	client->wait_data = 0;
	client->prompt = 1;
}

static void	check_client_fds(t_client *client)
{
	if (FD_ISSET(0, &client->fd_read))
		manage_cmd(client);
	if (client->fd > 0 && FD_ISSET(client->fd, &client->fd_read))
		server_recv(client);;
	if (client->fd > 0 && FD_ISSET(client->fd, &client->fd_write))
		server_send(client);
}

void	client_loop(t_client *client)
{
	int		max;

	while (1)
	{
		FD_ZERO(&client->fd_read);
		FD_ZERO(&client->fd_write);
		FD_SET(0, &client->fd_read);
		if (client->fd != 0)
		{
			FD_SET(client->fd, &client->fd_read);
			if (irc_strlen(client->buff_write))
				FD_SET(client->fd, &client->fd_write);
		}
		max = client->fd > 0 ? client->fd : 0;
		// ft_putstr("lock\n");
		select(max + 1, &client->fd_read, &client->fd_write, NULL, NULL);
		// ft_putstr("unlock\n");
		check_client_fds(client);
	}
}
