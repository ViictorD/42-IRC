/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:12:08 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 18:57:44 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

char	*get_next_word(char **str)
{
	char	*tmp;
	char	*out;

	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\v' \
			|| **str == '\r' || **str == '\f')
		++*str;
	tmp = *str;
	while (**str && (**str != ' ' && **str != '\t' && **str != '\n' && \
		**str != '\v' && **str != '\r' && **str != '\f'))
		++*str;
	if (!(*str - tmp))
		return (NULL);
	if (!(out = ft_memalloc(*str - tmp + 1)))
		ft_exiterror("Malloc failed.", 1);
	ft_memcpy(out, tmp, *str - tmp);
	return (out);
}

char	*pass_whitespace(char *msg)
{
	while (*msg == ' ' || *msg == '\t' || *msg == '\n' || *msg == '\v' \
			|| *msg == '\r' || *msg == '\f')
		++msg;
	if (!*msg)
		return (NULL);
	return (msg);
}

void	create_cmd1(char *dest, char *arg1)
{
	ft_strcpy(dest, arg1);
	ft_strcpy(dest + ft_strlen(arg1), "\r\n");
}

void	create_cmd2(char *dest, char *arg1, char *arg2)
{
	char	space;

	space = 0;
	ft_strcpy(dest, arg1);
	if (*(arg1 + ft_strlen(arg1) - 1) != ' ')
	{
		ft_strcpy(dest + ft_strlen(arg1), " ");
		space = 1;
	}
	ft_strcpy(dest + ft_strlen(arg1) + space, arg2);
	ft_strcpy(dest + ft_strlen(arg1) + space + ft_strlen(arg2), "\r\n");
}

void	create_cmd3(char *dest, char *arg1, char *arg2, char *arg3)
{
	char	space;

	space = 0;
	ft_strcpy(dest, arg1);
	if (*(arg1 + ft_strlen(arg1) - 1) != ' ')
	{
		ft_strcpy(dest + ft_strlen(arg1), " ");
		++space;
	}
	ft_strcpy(dest + ft_strlen(arg1) + space, arg2);
	if (*(arg2 + ft_strlen(arg2) - 1) != ' ')
	{
		ft_strcpy(dest + ft_strlen(arg1) + space + ft_strlen(arg2), " ");
		++space;
	}
	ft_strcpy(dest + ft_strlen(arg1) + space + ft_strlen(arg2), arg3);
	ft_strcpy(dest + ft_strlen(arg1) + space + ft_strlen(arg2) + \
		ft_strlen(arg3), "\r\n");
}
