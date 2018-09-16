/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_nick.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:46:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/14 16:48:15 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static char		user_already_exist(t_server *server, int fd, char *nick)
{
	int		i;

	i = -1;
	while (++i < server->max_fd)
	{
		if (server->fds[i].type == FD_CLIENT && i != fd && \
			!ft_strcmp(server->fds[i].username, nick))
			return (1);
	}
	return (0);
}

void		manage_nick(t_server *server, int fd)
{
	char	*tmp;
	char	*word;

	tmp = server->fds[fd].buff_read + 4;
	word = get_next_word(&tmp);
	if (!word)
	{
		reply_code(server, fd, ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (ft_strlen(word) > 9)
		reply_code(server, fd, ERR_UNAVAILRESOURCE);
	else if (user_already_exist(server, fd, word) || chan_exist(server, word))
		reply_code(server, fd, ERR_NICKCOLLISION);
	else
	{
		ft_strcpy(server->fds[fd].username, word);
		reply_code(server, fd, RPL_OK);
	}
	free(word);
}
