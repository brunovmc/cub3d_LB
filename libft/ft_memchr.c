/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:42:45 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/07 23:57:00 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *string, int caracter, size_t n)
{
	unsigned char	*s;
	unsigned char	c;
	unsigned int	i;

	s = (unsigned char *)string;
	c = (unsigned char)caracter;
	i = 0;
	while (i < n)
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
