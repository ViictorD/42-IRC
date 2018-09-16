/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_strlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:07:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/08 21:15:13 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t		irc_strlen(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str)
	{
		if (*str == '\r' && *(str + 1) == '\n')
			return ((str - tmp) + 2);
		++str;
	}
	return (0);
}