/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:30:26 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/09/10 15:44:00 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ascii.h"

void	ft_str_toupper(char *dest, char *src, size_t size)
{
	while (*src && size > 0)
	{
		*dest = ft_toupper(*src);
		++src;
		++dest;
		--size;
	}
}
