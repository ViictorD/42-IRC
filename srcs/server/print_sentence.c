/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sentenc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:59:26 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/16 19:01:44 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	print_sentence2(char *str1, char *str2)
{
	ft_putstr(str1);
	ft_putstr(str2);
	ft_putchar('\n');
}

void	print_sentence3(char *str1, char *str2, char *str3)
{
	ft_putstr(str1);
	ft_putstr(str2);
	ft_putstr(str3);
	ft_putchar('\n');
}
