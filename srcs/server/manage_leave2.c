/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_leave2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:14:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:14:48 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	reindex_connected(t_chan *chan, size_t i)
{
	while (i < chan->count)
	{
		chan->connected[i] = chan->connected[i + 1];
		++i;
	}
	chan->connected[i] = 0;
}
