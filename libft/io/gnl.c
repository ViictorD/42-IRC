/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:32:55 by bdurst            #+#    #+#             */
/*   Updated: 2018/09/09 13:48:04 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "string.h"
#include "list.h"
#include "gnl.h"
#include "io.h"

static char		*gnl_get_line(char *str, char **line, int *clean)
{
	int		i;

	i = 0;
	*clean = 1;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		ft_exiterror("malloc failure", 0);
	i = -1;
	while (str[++i] && str[i] != '\n')
		(*line)[i] = str[i];
	(*line)[i] = '\0';
	if (str[i] == '\n')
		i++;
	return (&str[i]);
}

int				gnl(int const fd, char **line)
{
	static char		*stock = NULL;
	char			buff[BUFFER_SIZE + 1];
	char			*tmp;
	int				ret;
	int				clean;

	clean = 0;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	ret = BUFFER_SIZE;
	while (!(ft_strchr(stock, '\n')) && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = stock;
		stock = ft_strjoin(stock, buff);
		if (tmp && clean)
			free(tmp);
	}
	if (ret == -1)
		return (-1);
	if (stock)
		stock = gnl_get_line(stock, line, &clean);
	if (!ret && (!stock || !*stock) && (!line || !*line || !**line))
		return (0);
	return (1);
}
