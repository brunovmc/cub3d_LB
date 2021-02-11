/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:56:20 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/07 23:53:18 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int caracter, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	c;
	unsigned int	i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	c = (unsigned char)caracter;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		if (source[i] == c)
			return (&dest[i + 1]);
		i++;
	}
	return (0);
}
