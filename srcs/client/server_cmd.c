/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 19:11:31 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:51:03 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char		check_valid_cmd(int i, char *str)
{
	if (!i || i == 1)
	{
		!i ? ft_putchar('\n') : 0;
		return (1);
	}
	if (i == CMD_BUFF)
	{
		ft_fputstr("irc: command too long\n", 2);
		while (str[0] != 10)
			read(0, str, 1);
		return (1);
	}
	return (0);
}

void		manage_cmd(t_client *client)
{
	char	str[CMD_BUFF];
	int		i;

	i = read(0, str, CMD_BUFF);
	if (check_valid_cmd(i, str))
		return ;
	str[i - 1] = '\0';
	if (check_cmd(str, "nick") || check_cmd(str, "join") || \
		check_cmd(str, "who") || check_cmd(str, "msg") || \
		check_cmd(str, "leave"))
	{
		if (!client->fd)
			ft_fputstr("Not connected to a server\n", 2);
		else
			create_cmd1(client->buff_write, str);
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

void		lost_connection(t_client *client)
{
	ft_putstr("\nLost connection with the server\n");
	clear_client(client);
}

void		save_read_client(t_client *client, int ret)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	len = 0;
	if (!client->save_read)
	{
		if (!(client->save_read = (char*)malloc(ret + 1)))
			ft_exiterror("Malloc failed", 1);
	}
	else
	{
		tmp = client->save_read;
		len = ft_strlen(tmp);
		if (!(client->save_read = (char*)malloc(len + ret + 1)))
			ft_exiterror("Malloc failed", 1);
		ft_strncpy(client->save_read, tmp, len);
	}
	ft_strncpy(client->save_read + len, client->buff_read, ret);
	client->save_read[len + ret] = '\0';
	if (tmp)
		free(tmp);
	ft_bzero(client->buff_read, BUFF_SIZE);
}
