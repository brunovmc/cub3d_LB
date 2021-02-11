/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:47:07 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/07 20:35:11 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t len)
{
	//size_t			i;
	unsigned char	*dst;
	unsigned char	*src;

	//i = 0;
	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	if (dst < src)
		return (ft_memcpy(dest, source, len));
	else
		while (dest != source && len--)
			dst[len] = src[len];
	return (dest);
}
