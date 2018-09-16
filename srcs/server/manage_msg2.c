/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_msg2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:20:35 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:21:14 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

char	user_exist(t_server *server, char *name)
{
	int		i;

	i = -1;
	while (++i < server->max_fd)
	{
		if (server->fds[i].type == FD_CLIENT && \
			!ft_strcmp(server->fds[i].username, name))
			return (1);
	}
	return (0);
}
