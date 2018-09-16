/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_chan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:03:04 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/13 18:21:30 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static t_chan	*new_chan(t_server *server, char *name)
{
	t_chan 	*new;

	new = (t_chan*)malloc(sizeof(struct s_chan));
	new->connected = (int*)malloc(sizeof(int) * server->max_fd);
	ft_bzero((void*)new->connected, server->max_fd * sizeof(int));
	if (*name == '#')
		++name;
	ft_strcpy(new->chan_name, name);
	ft_putstr("NEW CHAN \"");
	ft_putstr(new->chan_name);
	ft_putstr("\"\n");
	new->next = NULL;
	new->count = 0;
	return (new);
}

void		free_chan(t_chan *chan)
{
	free(chan->connected);
	if (chan->next)
		free(chan->next);
	free(chan);
}

void		delete_chan(t_server *server, t_chan *to_del)
{
	t_chan 	*prev;
	t_chan	*curr;

	curr = server->chan;
	prev = curr;
	while (curr)
	{
		if (curr == to_del)
		{
			ft_putstr("Chan ");
			ft_putstr(curr->chan_name);
			ft_putstr(" deleted\n");
			if (prev == curr)
			{
				server->chan = !curr->next ? NULL : curr->next;
				free_chan(curr);
			}
			else
			{
				prev->next = curr->next;
				free_chan(curr);
			}
			return ;
		}
		prev = curr;
		NEXT(curr);
	}
}

void		create_chan(t_server *server, char *name)
{
	t_chan		*chan;

	if (!server->chan)
		server->chan = new_chan(server, name);
	else
	{
		chan = server->chan;
		while (chan->next)
			NEXT(chan);
		chan->next = new_chan(server, name);
	}
}

char		chan_exist(t_server *server, char *name)
{
	t_chan		*chan;
	char		sharp;

	if (!server->chan)
		return (0);
	sharp = *name == '#' ? 1 : 0;
	chan = server->chan;
	while (chan)
	{
		if (!ft_strcmp(chan->chan_name, name + sharp))
			return (1);
		NEXT(chan);
	}
	return (0);
}
