/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 06:35:28 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/06 22:45:27 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*dest;
	const char		*source;

	dest = dst;
	source = (char *)src;
	i = 0;
	while (i < n && dst != src)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
